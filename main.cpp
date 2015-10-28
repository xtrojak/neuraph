#include "Net.cpp"
#include <iostream>

using namespace std;

// Activation functions
f64 threshold(double x)
{
    return (x >= 0) ? 1 : 0;
}

int main(int argc, char **argv)
{
    Net n = Net(std::vector<u32> {2, 2, 1}, &threshold);

    n.getLayer(0)[0].setWeights(std::vector<f64> {-1, 2, 2});
    n.getLayer(0)[1].setWeights(std::vector<f64> {3, -2, -2});
    n.getLayer(1)[0].setWeights(std::vector<f64> {-2, 1, 1});
    
    cout << "(0, 0) -> " << n.eval(std::vector<f64> {0, 0})[0] <<
        "\n(0, 1) -> " << n.eval(std::vector<f64> {0, 1})[0] <<
        "\n(1, 0) -> " << n.eval(std::vector<f64> {1, 0})[0] <<
        "\n(1, 1) -> " << n.eval(std::vector<f64> {1, 1})[0];

    return 0;
}
