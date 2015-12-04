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
            \tlearn chess.data my.net\n\
            \teval \"2 3 4 5 6 4 3 2 1 1 1 1 1 1 1 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 -1 -1 -1 -1 -1 -1 -1 -1 -2 -3 -4 -5 -6 -4 -3 -2\" my.net\n\n";
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
    else if (string(argv[1]) == "learn")
    {
        Net n(argv[3]);
        Chess c(argv[2]);
        
        list< tuple < vector<f64>, vector<f64> >> ideals;
        for (u32 i = 0; i < c.getMoveCount(); i++)
        {
            auto m = c.getMove(i);
            if (c.getMove(i).white)
                ideals.push_back(make_tuple(m.board,
                            vector<f64> {get<0>(m.from), get<1>(m.from), get<0>(m.to), get<1>(m.to)}));
        }

        u32 progress = 0, example_count = ideals.size();
        cout << "Learning on " << example_count << " examples.\n";

        Net newN = n;
        while (!ideals.empty())
        {
            list< tuple< vector<f64>, vector<f64>>> is;
            u32 dist = min(100u, u32(ideals.size()));
            is.splice(is.begin(), ideals, ideals.begin(), next(ideals.begin(), dist));
            newN = backprop(is, n);

            u32 new_p = 100-round((f64(ideals.size())/example_count)*100);
            if (progress != new_p)
            {
                cout << new_p << "%\n";
                progress = new_p;
            }
        }

        newN.serialize(argv[3]);
    }
    else if (string(argv[1]) == "eval")
    {
        Net n(argv[3]);
        auto input = Chess::parseBoard(argv[2]);
        Chess::printBoard(input);
        cout << endl;

        auto output = n.eval(input);
        Chess::printBoard(output);
    }
    else
    {
        cout << "Unknown argument\n";
    }


    return 0;
}
