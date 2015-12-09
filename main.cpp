#include "Net.cpp"
#include "Teacher.cpp"
#include "Polynoms.cpp"
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
        u32 example_count = stoi(argv[2]);
        example_count += 100 - (example_count % 100);

        Net n(argv[3]);
        Polynoms p(2, 2, example_count);
        Net newN = n;
        f64 progress = 0;
        
        cout << "Learning on " << example_count << " examples.\n";
        auto start = p.getPolynoms().begin(), end = start;
        advance(end, 100);

        do
        {
            list<tuple<vector<f64>, vector<f64>>> is(start, end);
            newN = backprop(is, 0.0001, newN);

            start = end;
            advance(end, 100);

            f64 op = progress;
            progress += f64(10000) / example_count;
            if (floor(op) != floor(progress))
            {
                    cout << round(progress) << "%\t";
                    cout.flush();
            }
        }
        while (start != p.getPolynoms().end());

        newN.serialize(argv[3]);
    }
    else if (string(argv[1]) == "eval")
    {
        Net n(argv[3]);
        auto input = Polynoms::parsePoly(argv[2]);
        Polynoms::print(input);
        cout << endl;

        auto output = n.eval(input);
        Polynoms::print(output);
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

