#include "types.h"
#include <algorithm>
#include <vector>
#include <random>

#define R 0.1f


class Neuron
{
    public:
        Neuron(u32 num_weights, f64 (*fun) (f64))
        {
            Sigma = fun;
            Potential = 0.f;
            
            Weights.resize(num_weights);
            std::mt19937 generator(23);
            std::uniform_real_distribution<f64> dis(-R, R);
            for_each(Weights.begin(), Weights.end(), [&](f64 x) { dis(generator); });
        }

        void setWeights(std::vector<f64> new_weights)
        {
            Weights = new_weights;
        }

        void calculate(std::vector<f64> inputs)
        {
            f64 acc = 0;
            for (u32 i = 0; i <= Weights.size(); i++)
            {
                acc += Weights[i] * inputs[i];
            }

            Potential = Sigma(acc);
        }

        f64 getPotential()
        {
            return Potential;
        }
            

    private:
        std::vector<f64> Weights;
        f64 (*Sigma) (f64);
        f64 Potential;
};
