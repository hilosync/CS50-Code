from cs50 import get_string
import string

totalLetters = 0
totalSentences = 0
totalWords = 1

f = get_string("Text: ")

for i in f:
    if i in list(string.ascii_lowercase) or i in list(string.ascii_uppercase):
        totalLetters += 1
    if i == "." or i == "!" or i == "?":
        totalSentences += 1

    if i == " ":
        totalWords += 1

averageLetters = totalLetters * (100/totalWords)
averageSentences = totalSentences * (100/totalWords)

solution = round(0.0588*averageLetters - (0.296*averageSentences) - 15.8)
if solution > 16:
    print("Grade 16+")
if solution < 1:
    print("Before Grade 1")
else:
    print("Grade " + str(solution))