import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():

    db.execute("DELETE FROM totals WHERE quantity=0;")

    """Show portfolio of stocks"""
    is_bought = db.execute('SELECT SUM(quantity) FROM totals WHERE userid = ?;', session["user_id"])
    current_balance = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])


    if not is_bought[0]['SUM(quantity)']:
        return render_template("index.html", is_buy=False, balance=usd(current_balance[0]['cash']))

    user = db.execute("SELECT username FROM users WHERE id = ?;", session["user_id"])
    symbol_quantity = db.execute("SELECT symbol, SUM(quantity) FROM totals WHERE userid = ? GROUP BY symbol;", session["user_id"])


    # print(current_balance)
    ans = list()
    total_stock_value = 0
    subtotal = current_balance[0]['cash']

    for qt in symbol_quantity:
        to_append = dict()
        to_append['symbol'] = qt['symbol']
        to_append['no_of_shares'] = qt['SUM(quantity)']
        to_append['current_share_price'] = lookup(qt['symbol'])['price']
        to_append['total_value'] = round(to_append['no_of_shares'] * to_append['current_share_price'])
        ans.append(to_append)
        total_stock_value += to_append['total_value']
        subtotal += to_append['total_value']



    return render_template("index.html", is_buy=True, username=user[0]['username'], current_cash_balance=usd(current_balance[0]['cash']), ans_to_iter=ans, usd_func=usd, total_stock_value=usd(total_stock_value), subtotal=usd(subtotal))




@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # print(session["user_id"])


    if request.method == "POST":
        response = lookup(request.form.get("symbol"))
        curr_balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])


        if not response or not request.form.get("symbol"):
            return apology("No such share", 400)

        try:
            if not request.form.get("shares") or int(request.form.get("shares")) < 1:
                return apology("No such quantity", 400)
        except ValueError:
            return apology("Please enter a valid number of shares", 400)

        total_price_of_shares = (response["price"] * int(request.form.get("shares")))

        if curr_balance[0]['cash'] - total_price_of_shares < 0:
            return apology("Insufficient funds", 400)

        db.execute("INSERT INTO buy VALUES (?, ?, ?, ?, datetime(), ?);", session["user_id"],
        response["symbol"], response["price"], request.form.get("shares"), 1)

        db.execute("UPDATE users SET cash = ? WHERE id = ?;", curr_balance[0]['cash'] - total_price_of_shares, session["user_id"])

        is_in_totals = db.execute("SELECT quantity FROM totals WHERE symbol=? AND userid=?", response["symbol"], session["user_id"])
        # print(is_in_totals)
        # print(len(is_in_totals))
        if len(is_in_totals) == 0:
            db.execute("INSERT INTO totals VALUES (?, ?, ?)", session["user_id"], response["symbol"], request.form.get("shares"))
        else:
            db.execute("UPDATE totals SET quantity=(SELECT quantity FROM totals WHERE symbol=? AND userid=?) + ? WHERE userid=? AND symbol=?;", response["symbol"], session["user_id"], request.form.get("shares"), session["user_id"], response["symbol"])



        return redirect("/")



    return render_template("buy.html")
    # return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    query = db.execute("SELECT symbol, price, quantity, date, is_buy FROM buy WHERE userid=? UNION ALL SELECT symbol, price, quantity, date, is_buy FROM sell WHERE userid=? ORDER BY date DESC;", session["user_id"], session["user_id"])

    if len(query) == 0:
        return render_template("history.html", answer=query, is_null=True)

    return render_template("history.html", answer=query, is_null=False)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

         # print(rows)
        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")




@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login formz
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    if request.method == "POST":
        response = lookup(request.form.get("symbol"))

        if response:

            return render_template("quoted.html", name=response['name'], price=usd(response['price']), symbol=response['symbol'])

        else:

            return apology("Invalid company symbol", 400)

    else:
        return render_template("quote.html")

    """Get stock quote."""
    # return apology("TODO")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) > 0 or len(request.form.get("username")) == 0:
            return apology("The username is already taken", 400)

        if len(request.form.get("password")) == 0 or request.form.get("password") != request.form.get("confirmation"):
            return apology("Invalid password", 400)

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))

        return redirect('/')

    else:
        return render_template("register.html")
    # return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        quantity_of_query = db.execute('SELECT quantity FROM totals WHERE userid = ? AND symbol = ? GROUP BY symbol;', session["user_id"], request.form.get("symbol"))

        # print("MY ANSWER: ", quantity_of_query)

        if not db.execute('SELECT quantity FROM totals WHERE userid = ? AND symbol = ?', session["user_id"], request.form.get("symbol")):
            return apology("Sorry, you don't have such stock", 400)

        # SELECT SUM(quantity) FROM buy WHERE userid = 1 AND symbol = "AAPL" GROUP BY symbol;
        if not request.form.get("shares") or int(request.form.get("shares")) < 1:
            return apology("No such quantity", 400)

        if int(request.form.get('shares')) > quantity_of_query[0]['quantity']:
            return apology("You cannot sell more than you have", 400)
        # update sell table
        db.execute("INSERT INTO sell VALUES (?, ?, ?, ?, datetime(), ?);", session["user_id"],
        request.form.get("symbol"), lookup(request.form.get("symbol"))['price'], request.form.get("shares"), 0)


        # update cash column of users table
        db.execute("UPDATE users SET cash = cash + ? WHERE id=?;", lookup(request.form.get("symbol"))['price'] * int(request.form.get("shares")), session["user_id"])


        # updating totals

        # is_in_totals = db.execute("SELECT quantity FROM totals WHERE symbol=? AND userid=?", request.form.get("symbol"), session["user_id"])

        # if len(is_in_totals) == 0:
        #     db.execute("INSERT INTO totals VALUES (?, ?, ?)", session["user_id"], response["symbol"], request.form.get("shares"))
        # else:
        db.execute("UPDATE totals SET quantity=(SELECT quantity FROM totals WHERE symbol=? AND userid=?) - ? WHERE userid=? AND symbol=?;", request.form.get("symbol"), session["user_id"], request.form.get("shares"), session["user_id"], request.form.get("symbol"))


        return redirect('/')

    else:

        is_active = db.execute('SELECT SUM(quantity) FROM totals WHERE userid = ?;', session["user_id"])

        if not is_active[0]['SUM(quantity)']:
            return render_template("sell.html", is_active=False)

        active_symbols = db.execute('SELECT symbol FROM totals WHERE userid=? GROUP BY symbol;', session["user_id"])
        return render_template("sell.html", is_active=True, active_symbols=active_symbols)



@app.route("/reset", methods=["GET", "POST"])
@login_required
def reset():
    if request.method == "POST":
        first = request.form.get("pass")
        second = request.form.get("pass_2")


        if first != second:
            return render_template("reset.html", is_error=True)

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(request.form.get("pass")), session["user_id"])


        session.clear()
        return redirect("/")

    return render_template("reset.html")

if __name__ == "__main__":
    app.run(host='0.0.0.0', port=8080, debug=True)