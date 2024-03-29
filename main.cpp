#include "Net.cpp"
#include "Teacher.cpp"
#include "Chess.cpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

void test_and();

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
            if (c.getMove(i).white)
                ideals.push_back(make_tuple(c.getMove(i).board, c.getMove(i).boardAfter));
        }

        u32 progress = 0, example_count = ideals.size();
        cout << "Learning on " << example_count << " examples.\n";

        Net newN = n;
        while (!ideals.empty())
        {
            list< tuple< vector<f64>, vector<f64>>> is;
            u32 dist = min(100u, u32(ideals.size()));
            is.splice(is.begin(), ideals, ideals.begin(), next(ideals.begin(), dist));
            newN = backprop(is, 1, newN);

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
    else if (string(argv[1]) == "test")
    {
        test_and();
    }
    else
    {
        cout << "Unknown argument\n";
    }


    return 0;
}


void test_and()
{
    Net n(vector <u32> {2, 2, 1},
            [](f64 x, bool d) {
            if (d)
            {
                f64 ex = exp(x);
                f64 ex1 = 1 + ex;
                return ex / (ex1*ex1);
            }
            else
                return 1.0 / (1 + exp(-x));
            });
    
    list <tuple <vector <f64>, vector<f64> > > examples;
    examples.push_back(make_tuple(vector <f64> {0, 0}, vector <f64> {0}));
    examples.push_back(make_tuple(vector <f64> {1, 0}, vector <f64> {0}));
    examples.push_back(make_tuple(vector <f64> {1, 1}, vector <f64> {1}));
    
    for (u32 i = 0; i < 200; i++)
        n = backprop(examples, 1, n);

    cout << "0 AND 0 -> " << n.eval(vector <f64> {0, 0})[0] <<
        "\n0 AND 1 -> " << n.eval(vector <f64> {0, 1})[0] <<
        "\n1 AND 0 -> " << n.eval(vector <f64> {1, 0})[0] <<
        "\n1 AND 1 -> " << n.eval(vector <f64> {1, 1})[0] << "\n";
}

