#include "types.h"
#include "Neuron.cpp"
#include <vector>


class Net
{
    public:
        Net(std::vector<u32> layers, f64 (*fun) (f64), f64 (*dfun) (f64))
        {
            for (u32 i = 1; i < layers.size(); i++)
            {
                std::vector<Neuron> layer;
                layer.assign(layers[i], Neuron(layers[i-1], fun, dfun));
                Layers.push_back(layer);
            }
        }

        std::vector<f64> eval(std::vector<f64> inputs)
        {
            for (u32 i = 0; i < Layers.size(); i++)
            {
                inputs = eval_layer(i, inputs);
            }

            return inputs;
        }

        std::vector<Neuron>& getLayer(u32 layer)
        {
            return Layers[layer];
        }

        const f64 getLayerCount() const
        {
            return Layers.size();
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

