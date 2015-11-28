#include "Net.cpp"
#include "Teacher.cpp"
#include <iostream>
#include <math.h>

using namespace std;


// Activation functions
f64 linear(f64 x)
{
    return (x >= 0) ? 1 : 0;
}

f64 sigmoidal(f64 x)
{
    return 1.0 / (1 + exp(x));
}

f64 dsigmoidal(f64 x)
{
    f64 ex = exp(x);
    f64 ex1 = 1 + ex;
    return -ex / (ex1*ex1);
}

f64 tanhal(f64 x)
{
    return 6 * tanh ( x / 6.0 );
}

f64 dtanhal(f64 x)
{
    coshx6 = cosh ( x / 6.0 );
    coshx3 = cosh ( x / 3.0 ) + 1;
    return ( 4 * coshx6 * coshx6 ) / ( coshx3 * coshx3 );
}

int main(int argc, char **argv)
{
    Net n = Net(std::vector<u32> {2, 2, 1}, &sigmoidal, &dsigmoidal);
    
    

    n.print();
    cout << "\n";

//    n.getNeuron(1, 0).setWeights(std::vector<f64> {-1, 2, 2});
//    n.getNeuron(1, 1).setWeights(std::vector<f64> {3, -2, -2});
//    n.getNeuron(2, 0).setWeights(std::vector<f64> {-2, 1, 1});

    n.print();
    cout << "\n";

//    cout << "(0, 0) -> " << n.eval(std::vector<f64> {0, 0})[0] <<
//        "\n(0, 1) -> " << n.eval(std::vector<f64> {0, 1})[0] <<
//        "\n(1, 0) -> " << n.eval(std::vector<f64> {1, 0})[0] <<
//        "\n(1, 1) -> " << n.eval(std::vector<f64> {1:w
, 1})[0];


    vector< tuple< vector<f64>, vector<f64> >> data = {
        make_tuple(vector<f64> {1,1,1}, vector<f64> {1}),
        make_tuple(vector<f64> {1,1,0}, vector<f64> {1}),
        make_tuple(vector<f64> {1,0,1}, vector<f64> {1}),
        make_tuple(vector<f64> {1,0,0}, vector<f64> {1}),
        make_tuple(vector<f64> {0,1,1}, vector<f64> {1}),
        make_tuple(vector<f64> {0,1,0}, vector<f64> {1}),
        make_tuple(vector<f64> {0,0,1}, vector<f64> {1}),
        make_tuple(vector<f64> {0,0,0}, vector<f64> {0})
    };
//    vector< tuple< vector<f64>, vector<f64> >> data = {
//        make_tuple(vector<f64> {1,1}, vector<f64> {0}),
//        make_tuple(vector<f64> {0,0}, vector<f64> {0}),
//        make_tuple(vector<f64> {1,0}, vector<f64> {1}),
//        make_tuple(vector<f64> {0,1}, vector<f64> {1})
//    };

    cout << "\n";

    for (u32 i = 0; i < 500; i++)
        n = backtrack(data, n);

    n.print();
    cout << "\n";
    
    cout << "(1, 1, 1) -> " << n.eval(std::vector<f64> {1, 1, 1})[0] <<
       "\n(1, 1, 0) -> " << n.eval(std::vector<f64> {1, 1, 0})[0] <<
        "\n(1, 0, 1) -> " << n.eval(std::vector<f64> {1, 0, 1})[0] <<
        "\n(1, 0, 0) -> " << n.eval(std::vector<f64> {1, 0, 0})[0] <<
        "\n(0, 1, 1) -> " << n.eval(std::vector<f64> {0, 1, 1})[0] <<
        "\n(0, 1, 0) -> " << n.eval(std::vector<f64> {0, 1, 0})[0] <<
        "\n(0, 0, 1) -> " << n.eval(std::vector<f64> {0, 0, 1})[0] <<
        "\n(0, 0, 0) -> " << n.eval(std::vector<f64> {0, 0, 0})[0];

    cout << "\n";

//    cout << "(0, 0) -> " << n.eval(std::vector<f64> {0, 0})[0] <<
//        "\n(0, 1) -> " << n.eval(std::vector<f64> {0, 1})[0] <<
//        "\n(1, 0) -> " << n.eval(std::vector<f64> {1, 0})[0] <<
//        "\n(1, 1) -> " << n.eval(std::vector<f64> {1, 1})[0];

    return 0;
}
