import os
import werkzeug

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd



# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    
    if request.method == "POST":
        currentCash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        amountToAdd = request.form.get("amount")
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (float(currentCash[0]["cash"]) + (float(amountToAdd))), session["user_id"])
        
    
    
    currentUser = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    ownedStocks = db.execute("SELECT * FROM portfolio WHERE id = ?", session["user_id"])
    totalStockPrice = 0.0
    stockList = []
    
    if ownedStocks == []:
        return render_template("portfolio.html", currentUser = currentUser, totalStockPrice = totalStockPrice, stockList = stockList)
        
    
    x = 0
    currentStock = ""
    for row in ownedStocks:
        totalStockPrice += row["price"]
        if currentStock == row["stock"]:
            stockList[0]["amount"] += 1
            continue
        
        companyName = lookup(row["stock"])
        
        stockList.append({"stock":row["stock"], "price":row["price"], "name":companyName["name"], "amount":1})
        currentStock = row["stock"]
        x += 1
    
    return render_template("portfolio.html", currentUser = currentUser, totalStockPrice = totalStockPrice, stockList = stockList)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        amountToBuy = request.form.get("shares")
        if lookup(request.form.get("symbol")) == None:
            return apology("Invalid Symbol")

        if not amountToBuy:
            return apology("Invalid amount")
        
        if not float(amountToBuy).is_integer():
            return apology("Invalid amount")
            
        if not int(amountToBuy) > 0:
            return apology("Invalid amount")
            
        currentCash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        priceOfShare = lookup(request.form.get("symbol"))
        
        if (float(priceOfShare["price"]) * float(request.form.get("shares"))) > float(currentCash[0]["cash"]):
            return apology("Not enough cash in account")
            
        x = 0
        while x < int(request.form.get("shares")):
            db.execute("INSERT INTO portfolio  (id, stock, price) VALUES(?, ?, ?)", session["user_id"], request.form.get("symbol"), priceOfShare["price"])
            x = x + 1
        
        db.execute("INSERT INTO history (id, stock, price, amount) VALUES(?, ?, ?, ?)", session["user_id"], request.form.get("symbol"), priceOfShare["price"], int(request.form.get("shares")))
        
        db.execute("UPDATE users SET cash = ? WHERE id = ?", (float(currentCash[0]["cash"]) - (float(priceOfShare["price"]) * float(request.form.get("shares")))), session["user_id"])
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    
    stockList = db.execute("SELECT * FROM history WHERE id = ?", session["user_id"])
    
    
    return render_template("history.html", stockList = stockList)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

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

    # Redirect user to login form
    return redirect("/")


finalQuote = {}
@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    
    if request.method == "POST":
        return redirect("/quoted")
        
    else:
        return render_template("quote.html")
      
@app.route("/quoted", methods=["GET", "POST"])
def quoted():
    quoteSymbol = str(request.form.get("symbol"))
    finalQuote = lookup(quoteSymbol)
    
    if not quoteSymbol:
        return apology("Invalid Symbol")
    
    if not lookup(quoteSymbol):
        return apology("Invalid Symbol")
    return render_template("quoted.html", FINALQUOTE = finalQuote)


@app.route("/register", methods=["GET", "POST"])
def register():
    
    if request.method == "POST":
        if request.form.get("username") == "" or request.form.get("password") == "" or request.form.get("password") != request.form.get("confirmation"):
            return apology("Invalid Username / Password")
        else:
            Username = request.form.get("username")
            
            if db.execute("SELECT username FROM users WHERE username = ?", Username):
                return apology("Username already exists")
            
            passwordHash = werkzeug.security.generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)
            db.execute("INSERT INTO users  (username, hash) VALUES(?, ?)", Username, passwordHash)
            
            return redirect("/login")
            
    
    if request.method == "GET":
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    stockList = db.execute("SELECT DISTINCT * FROM portfolio WHERE id = ?", session["user_id"])
    if request.method == "POST":
        stockToSell = request.form.get("symbol")
        amountToSell = float(request.form.get("shares"))
        priceOfShare = lookup(stockToSell)
        
        amountOwned = int(db.execute("SELECT COUNT(stock) FROM portfolio WHERE id = ? AND stock = ?", session["user_id"], stockToSell)[0]["COUNT(stock)"])
        if not amountToSell:
            return apology("Invalid amount")
        
        if not amountToSell.is_integer():
            return apology("Invalid amount")
        
        if int(amountToSell) > amountOwned:
            return apology("Invalid amount")
        

            
            
        
        x = 0
        while x < int(amountToSell):
            db.execute("DELETE FROM portfolio WHERE id = ? AND stock = ? LIMIT 1", session["user_id"], stockToSell)
            x = x + 1
        db.execute("UPDATE users SET cash = ? WHERE id = ?", float(db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"] + (float(priceOfShare["price"]) * float(amountToSell))), session["user_id"])
        
        db.execute("INSERT INTO history (id, stock, price, amount) VALUES(?, ?, ?, ?)", session["user_id"], stockToSell, float(priceOfShare["price"]), -int(amountToSell))
        
        return redirect("/")
    else:
        return render_template("sell.html", stockList = stockList)
    
    


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
