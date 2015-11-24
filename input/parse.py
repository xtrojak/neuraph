"""
USAGE: python parse.py <input file>
"""

#GLOBALS
# Pawn = 1, Rook = 2, kNight = 3, Bishop = 4, Queen = 5, King = 6
WHITE = "prnbqk"
BLACK = "PRNBQK"
NUMBERS = "12345678"
LETTERS = "ABCDEFGH"

import sys

"""
Transforms FEN format line by line to "our" chess format
:param inputfile: textfile with a FEN on each line
"""
def applyTransform(inputfile):
    ff = open(inputfile, 'r')
    FENs = ff.readlines()
    FEN1 = FENs[0]
    for i in range(1, len(FENs)):
        FEN2 = FENs[i]
        if not FEN2.split(' ', 1)[0] == "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR":
            FEN1 = fenToChess(FEN1)
            FEN2 = fenToChess(FEN2)
            change = calcMove(FEN1, FEN2)
            FEN1 = str(FEN1).translate(None, '[],')
            FEN2 = str(FEN2).translate(None, '[],')
            change = str(change).translate(None, '(),\'')
            f.write(FEN1.__str__() + '\n')
            f.write(FEN2.__str__() + '\n')
            f.write(change.__str__() + '\n')
            f.write('\n')
        FEN1 = FENs[i]

def calcMove(FEN1, FEN2):
    move_from = ""
    move_to = ""
    who = ""
    for i in range(len(FEN1)):
        if FEN1[i] != FEN2[i]:
            if FEN2[i] == 0:
                who = "b" if FEN1[i] < 0 else "w"
                move_from = str(i%8 + 1) + ' ' + str(i/8 + 1)
            else:
                move_to = str(i%8 + 1) + ' ' + str(i/8 + 1)
    change = (who, move_from, move_to)
    return change

"""
Transforms one FEN and writes "chess" format to output.txt
:param FEN: one FEN in string format
"""
def fenToChess(FEN):
    FEN = FEN.split(' ', 1)[0]
    rows = FEN.split('/')
    row = toNumber(rows)
    return row

"""
Transforms one character to specific number (see global values)
:param char: a character from FEN format
:return:
"""
def toNumber(rows):
    new_row = []
    for row in rows:
        for char in row:
            if char in WHITE:
                new_row.append(WHITE.index(char) + 1)
            elif char in BLACK:
                new_row.append(-(BLACK.index(char) + 1))
            elif char in NUMBERS:
                new_row += [0 for s in xrange(NUMBERS.index(char) + 1)]
            else:
                print "watafak"
    return new_row


inputfile = sys.argv[-1]
f = open('output.txt','w')
applyTransform(inputfile)