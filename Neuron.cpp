#ifndef NEURON_INCLUDED
#define NEURON_INCLUDED

#include "types.h"
#include <algorithm>
#include <vector>
#include <random>
#include <iostream>

#define RAND_INIT 0.1f


class Neuron
{
    public:
        Neuron(u32 num_weights, f64 (*fun) (f64), f64 (*dfun) (f64))
        {
            Sigma = fun;
            dSigma = dfun;
            Output = 0.f;
            
            std::random_device generator;
            std::uniform_real_distribution<f64> dis(-RAND_INIT, RAND_INIT);
            for (u32 i = 0; i < num_weights; i++)
                Weights.push_back(dis(generator));
        }

        void setWeights(const std::vector<f64> &new_weights)
        {
            Weights = new_weights;
        }

        const std::vector<f64> getWeights() const
        {
            return Weights;
        }

        std::vector<f64> getWeights()
        {
            return Weights;
        }

        f64 calculate(const std::vector<f64> &inputs)
        {
            //std::cout << "W:" << Weights.size() << " I:" << inputs.size() << "\n";
            f64 acc = Weights[0];
            for (u32 i = 1; i < Weights.size(); i++)
            {
                acc += Weights[i] * inputs[i-1];
            }
            
            Output = Sigma(acc);
            dOutput = dSigma(acc);
            return Output;
        }
        
        f64 getOutput()
        {
            return Output;
        }

        f64 getdOutput()
        {
            return dOutput;
        }

    private:
        std::vector<f64> Weights;
        f64 (*Sigma) (f64);
        f64 (*dSigma) (f64);
        f64 Output, dOutput;
};

#endif
