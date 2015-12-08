#ifndef NEURON_INCLUDED
#define NEURON_INCLUDED

#include "types.h"
#include <vector>
#include <random>
#include <iostream>

#define RAND_INIT 0.1f


class Neuron
{
    public:
        Neuron(u32 num_weights, f64 (*fun) (f64, bool))
        {
            ActivationFn = fun;
            Output = 0.f;
            
            std::random_device generator;
            std::uniform_real_distribution<f64> dis(-RAND_INIT, RAND_INIT);
            for (u32 i = 0; i < num_weights; i++)
                Weights.push_back(dis(generator));
        }

        const u32 getWeightCount() const
        {
            return Weights.size();
        }

        // Remember that the 0th weight is the neuron bias.
        f64& getWeight(u32 index)
        {
            return Weights[index];
        }

        const f64 getWeight(u32 index) const
        {
            return Weights[index];
        }

        f64 calculate(const std::vector<f64> &inputs)
        {
            f64 acc = Weights[0];
            for (u32 i = 1; i < Weights.size(); i++)
            {
                acc += Weights[i] * inputs[i-1];
            }
            
            Output = ActivationFn(acc, false);
            dOutput = ActivationFn(acc, true);
            return Output;
        }

        void print() const
        {
            for (u32 i = 0; i < Weights.size(); i++)
                std::cout << Weights[i] << " ";
        }
        
        void setOutput(f64 o)
        {
            Output = o;
        }
        
        const f64 getOutput() const
        {
            return Output;
        }

        const f64 getdOutput() const
        {
            return dOutput;
        }

        void setWeights(std::vector<f64> vec)
        {
            Weights = vec;
        }

    private:
        std::vector<f64> Weights;
        f64 (*ActivationFn) (f64, bool);
        f64 Output, dOutput;
};

#endif
