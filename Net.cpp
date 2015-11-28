#ifndef NET_INCLUDED
#define NET_INCLUDED

#include "types.h"
#include "Neuron.cpp"
#include <vector>
#include <iostream>


class Net
{
    public:
        Net(std::vector<u32> layers)
        {
            layers.insert(layers.begin(), 0);
            for (u32 i = 1; i < layers.size(); i++)
            {
                std::vector<Neuron> layer;
                layer.assign(layers[i], Neuron(layers[i-1]+1, &sigmoidal, &dsigmoidal));
                Layers.push_back(layer);
            }
        }

        std::vector<f64> eval(std::vector<f64> inputs)
        {
            for (u32 i = 0; i < Layers[0].size(); i++)
                Layers[0][i].setOutput(inputs[i]);

            for (u32 i = 1; i < Layers.size(); i++)
            {
                inputs = eval_layer(i, inputs);
            }

            return inputs;
        }

        void print() const
        {
            for (i32 i = Layers.size() - 1; i >= 0; --i)
            {
                for (u32 j = 0; j < Layers[i].size(); j++)
                {
                    Layers[i][j].print();
                    std::cout << "|";
                }
                std::cout << "\n";
            }
        }

        const std::vector<Neuron> &getLayer(u32 layer) const
        {
            return Layers.at(layer);
        }

        Neuron &getNeuron(u32 layer, u32 neuron)
        {
            return Layers.at(layer).at(neuron);
        }

        const u32 getLayerCount() const
        {
            return Layers.size();
        }
        
        // Activation functions 
		static f64 sigmoidal(f64 x) 
		{ 
			return 1.0 / (1 + exp(x)); 
		} 

		static f64 dsigmoidal(f64 x) 
		{ 
			f64 ex = exp(x); 
			f64 ex1 = 1 + ex; 
			return -ex / (ex1*ex1); 
		}

    private:
        std::vector<f64> eval_layer(u32 layer, const std::vector<f64> &ins)
        {
            u32 neuron_count = Layers[layer].size();
            std::vector<f64> res; 
            res.resize(neuron_count);

            for (u32 i = 0; i < neuron_count; i++)
            {
                res[i] = Layers[layer][i].calculate(ins);
            }

            return res;
        }


        std::vector< std::vector<Neuron> > Layers;

};

#endif
