from cs50 import get_int
x = True

while (x):
    f = get_int("Height: ")
    if f >= 1 and f <= 8:
        x = False

for i in range(1,f+1):
    print(' '*(f-i) + '#' * (i))

