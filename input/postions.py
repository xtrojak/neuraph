"""
USAGE: python positions.py <input file>
"""

#GLOBALS
#Pieces have this order: KkQqBBbbNNnnRRrrPPPPPPPPpppppppp
import sys
NUMBERS = "12345678"

"""
Transforms FEN format line by line to position format
:param inputfile: textfile with a FEN on each line
"""
def applyTransform(inputfile):
    ff = open(inputfile, 'r')
    FENs = ff.readlines()
    FEN1 = FENs[0]
    for i in range(1, len(FENs)):
        FEN2 = FENs[i]
        if not FEN2.split(' ', 1)[0] == "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR":
            who = FEN1.split(' ')[1]
            FEN1= calPositions(transformFEN(FEN1))
            FEN2 = calPositions(transformFEN(FEN2))
            move = calcMove(FEN1, FEN2, who)
            FEN1 = str(FEN1).translate(None, '()[],')
            FEN2 = str(FEN2).translate(None, '()[],')
            move = str(move).translate(None, '(),')
            f.write(FEN1.__str__() + '\n' + FEN2.__str__() + '\n' + move.__str__() + '\n\n')
        FEN1 = FENs[i]

"""
Calculates one move
:param FEN: two position FENs and ID of player (bLACK or wHITE)
"""
def calcMove(FEN1, FEN2, who):
    move = ""
    for i in range(len(FEN1)):
        if FEN1[i] != FEN2[i]:
            if FEN2[i] != (0, 0):
                move = who + " " + str(FEN1[i]) + " " + str(FEN2[i])
    return move


def transformFEN(FEN):
    FEN = FEN.split(' ')[0]
    rows = FEN.split('/')
    row = expand(rows)
    return row

"""
Expands one FEN [ via transformFEN() ]
:param FEN: one FEN in string format
"""
def expand(rows):
    new_FEN = []
    for row in rows:
        new_row = []
        for char in row:
            if char in NUMBERS:
                new_row += ['0' for s in xrange(NUMBERS.index(char) + 1)]
            else:
                new_row.append(char)
        new_FEN.append(new_row)
    return new_FEN

"""
Transforms expanded FEN to positions of pieces on chessboard
:param FEN: one expanded FEN in string format
"""
def calPositions(FEN):
    positions = "KkQqBBbbNNnnRRrrPPPPPPPPpppppppp"
    output = [(0, 0) for n in range(32)]
    for i in range(8):
        for j in range(8):
            position = positions.find(FEN[i][j])
            if position != -1:
                positions = positions[:position] + 'X' + positions[position + 1:]
                output[position] = (i + 1, j + 1)
    return output

inputfile = sys.argv[-1]
f = open('output.txt','w')
applyTransform(inputfile)