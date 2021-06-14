import csv
import sys
import random


def SequencerFunction(DNAsequence, STR):
    count = [0] * len(DNAsequence)
    for i in range(len(DNAsequence) - len(STR),-1,-1):
        if (str(DNAsequence[i:i+(len(STR))]) == str(STR)):
            if i + len(STR) > len(DNAsequence)-1:
                count[i] = 1
            else:
                count[i] = count[i +len(STR)] + 1
    return max(count)


if len(sys.argv) != 3:
    sys.exit("Usage: python dna.py data.csv sequence.txt")



in_file = open(sys.argv[2], 'r')
sequence = in_file.read()



with open(sys.argv[1]) as file:
    reader = csv.DictReader(file)
    for row in reader:
        i = 1
        matchCheck = 0
        while i < len(row):
            listOfKeys= list(row.keys())
            #print(listOfKeys[i] + " " + str(SequencerFunction(sequence, listOfKeys[i])))
            #print(row[listOfKeys[i]])
            if (int(row[listOfKeys[i]]) == int(SequencerFunction(sequence, listOfKeys[i]))):
                #print(row[listOfKeys[i]])
                matchCheck += 1
                i+=1
                #print(matchCheck)
            else:
                i+=1
        if matchCheck == (len(row)-1):
            print(row['name'])
            sys.exit()


print("No match")









