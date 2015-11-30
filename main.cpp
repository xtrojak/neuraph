#include "Net.cpp"
#include "Teacher.cpp"
#include "Chess.cpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;


int main(int argc, char **argv)
{
    if (argc < 2 || string(argv[1]) == "help")
    {
        cout << "Example usage:\n\t" << argv[0] <<
            "\tnew \"2 3 3 2\" my.net\n\
            \tteach my.net chess.data\n\
            \teval \"2 3 4 5 6 4 3 2 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1 -1 -1 -1 -1 -1 -1 -1 -2 -3 -4 -5 -6 -4 -3 -2\"\n\n";
    }
    else if (string(argv[1]) == "new")
    {
        std::vector<u32> topology;
        char *tok = strtok(argv[2], " ");
        while (tok != NULL)
        {
            topology.push_back(std::stoi(tok));
            tok = strtok(NULL, " ");
        }

        Net n(topology);
        n.serialize(argv[3]);
    }
    else if (string(argv[1]) == "teach")
    {
        Net n(argv[2]);
        Chess c(argv[3]);
        
        list< tuple < vector<f64>, vector<f64> >> ideals;
        for (u32 i = 0; i < c.getMoveCount(); i++)
        {
            if (c.getMove(i).white)
                ideals.push_back(make_tuple(c.getMove(i).board, c.getMove(i).boardAfter));
        }

        Net newN = n;
        while (!ideals.empty())
        {
            list< tuple< vector<f64>, vector<f64>>> is;
            u32 dist = min(100u, u32(ideals.size()));
            is.splice(is.begin(), ideals, ideals.begin(), next(ideals.begin(), dist));
            newN = backprop(is, n);
        }
        newN.serialize(argv[2]);
    }
    else if (string(argv[1]) == "eval")
    {
        Net n(argv[2]);
        auto input = Chess::parseBoard(argv[3]);
        Chess::printBoard(input);
        auto output = n.eval(input);
        Chess::printBoard(output);
    }
    else
    {
        cout << "Unknown argument\n";
    }


    return 0;
}
