#include "Net.cpp"
#include "Teacher.cpp"
#include "Chess.cpp"

#include <iostream>
#include <math.h>

using namespace std;


int main(int argc, char **argv)
{
    Net n = Net(std::vector<u32> {2, 2, 1});
    
    Chess c("output.txt");
    cout << get<0>(c.getMoves()[2].from) << endl;

    n.print();
    cout << "\n";

    n.getNeuron(1, 0).setWeights(std::vector<f64> {-1, 2, 2});
    n.getNeuron(1, 1).setWeights(std::vector<f64> {3, -2, -2});
    n.getNeuron(2, 0).setWeights(std::vector<f64> {-2, 1, 1});

    n.print();
    cout << "\n";

    cout << "(0, 0) -> " << n.eval(std::vector<f64> {0, 0})[0] <<
        "\n(0, 1) -> " << n.eval(std::vector<f64> {0, 1})[0] <<
        "\n(1, 0) -> " << n.eval(std::vector<f64> {1, 0})[0] <<
        "\n(1, 1) -> " << n.eval(std::vector<f64> {1, 1})[0];


//    vector< tuple< vector<f64>, vector<f64> >> data = {
//        make_tuple(vector<f64> {1,1,1}, vector<f64> {1}),
//        make_tuple(vector<f64> {1,1,0}, vector<f64> {0}),
//        make_tuple(vector<f64> {1,0,1}, vector<f64> {1}),
//        make_tuple(vector<f64> {1,0,0}, vector<f64> {1}),
//        make_tuple(vector<f64> {0,1,1}, vector<f64> {1}),
//        make_tuple(vector<f64> {0,1,0}, vector<f64> {0}),
//        make_tuple(vector<f64> {0,0,1}, vector<f64> {1}),
//        make_tuple(vector<f64> {0,0,0}, vector<f64> {0})
//    };
    vector< tuple< vector<f64>, vector<f64> >> data = {
        make_tuple(vector<f64> {1,1}, vector<f64> {0}),
        make_tuple(vector<f64> {0,0}, vector<f64> {0}),
        make_tuple(vector<f64> {1,0}, vector<f64> {1}),
        make_tuple(vector<f64> {0,1}, vector<f64> {1})
    };

    cout << "\n";

    for (u32 i = 0; i < 500; i++)
        n = backtrack(data, n);

    n.print();
    cout << "\n";
    
//    cout << "(1, 1, 1) -> " << n.eval(std::vector<f64> {1, 1, 1})[0] <<
//       "\n(1, 1, 0) -> " << n.eval(std::vector<f64> {1, 1, 0})[0] <<
//        "\n(1, 0, 1) -> " << n.eval(std::vector<f64> {1, 0, 1})[0] <<
//        "\n(1, 0, 0) -> " << n.eval(std::vector<f64> {1, 0, 0})[0] <<
//        "\n(0, 1, 1) -> " << n.eval(std::vector<f64> {0, 1, 1})[0] <<
//        "\n(0, 1, 0) -> " << n.eval(std::vector<f64> {0, 1, 0})[0] <<
//        "\n(0, 0, 1) -> " << n.eval(std::vector<f64> {0, 0, 1})[0] <<
//        "\n(0, 0, 0) -> " << n.eval(std::vector<f64> {0, 0, 0})[0];
//
//    cout << "\n";

    cout << "(0, 0) -> " << n.eval(std::vector<f64> {0, 0})[0] <<
        "\n(0, 1) -> " << n.eval(std::vector<f64> {0, 1})[0] <<
        "\n(1, 0) -> " << n.eval(std::vector<f64> {1, 0})[0] <<
        "\n(1, 1) -> " << n.eval(std::vector<f64> {1, 1})[0];

    return 0;
}
