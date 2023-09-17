import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        if not request.form.get('name') or not request.form.get('month') or not request.form.get('day'):
            return redirect('/')
        if not request.form.get('month').isdigit() or not request.form.get('day'):
            return redirect('/')

        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", request.form.get('name'), request.form.get('month'),
        request.form.get('day'))

        return redirect("/")

    else:

        birthday_info = db.execute("SELECT birthdays.name, birthdays.month, birthdays.day FROM birthdays;")

        return render_template("index.html", birthday_info=birthday_info)


app.run(host='0.0.0.0', port=8080, debug=True)