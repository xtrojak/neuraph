"""
USAGE: python parse.py <input file>
"""

#GLOBALS
# Pawn = 1, Rook = 2, kNight = 3, Bishop = 4, Queen = 5, King = 6
WHITE = "prnbqk"
BLACK = "PRNBQK"
NUMBERS = "12345678"

import sys

"""
Transforms FEN format line by line to "our" chess format
:param inputfile: textfile with a FEN on each line
"""
def applyTransform(inputfile):
    with open(inputfile) as FENs:
        for FEN in FENs:
            fenToChess(FEN)
            f.write('\n')

"""
Transforms one FEN and writes "chess" format to output.txt
:param FEN: one FEN in string format
"""
def fenToChess(FEN):
    FEN = FEN.split(' ', 1)[0]
    if FEN == "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR":
        f.write("New game" + '\n' + '\n')
    rows = FEN.split('/')
    for row in rows:
        new_row = ""
        for char in row:
            new_row += toNumber(char)
        f.write(new_row.__str__() + '\n')

"""
Transforms one character to specific number (see global values)
:param char: a character from FEN format
:return:
"""
def toNumber(char):
    if char in WHITE:
        return " " + str(WHITE.index(char) + 1)
    elif char in BLACK:
        return str(-(BLACK.index(char) + 1))
    elif char in NUMBERS:
        return ''.join([' 0' for s in xrange(NUMBERS.index(char) + 1)])
    else:
        print "watafak"


inputfile = sys.argv[-1]
f = open('output.txt','w')

applyTransform(inputfile)