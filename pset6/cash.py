from cs50 import get_float
f = -0.1

while f < 0:
    f = get_float("Change owed: ")

coins = 0

while (f - 0.24999) >= 0.0000:
    f -= 0.25
    coins += 1

while (f - 0.0999999) >= 0.0000:
    f -= 0.10
    coins += 1

while (f - 0.04999) >= 0.0000:
    f -= 0.05
    coins += 1

while (f - 0.00999) >= 0.0000:
    f -= 0.01
    coins += 1

print(str(coins) + "\n")


