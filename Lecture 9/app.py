from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")

@app.route("/greet", methods=["POST"])
def greet():
    name = request.form.get("name")
    if len(name) == 0:
        name =  "world"
    return render_template("greet.html", name=name)



app.run(host='0.0.0.0', port=8080,
debug=True)