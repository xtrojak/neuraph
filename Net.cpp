#ifndef NET_INCLUDED
#define NET_INCLUDED

#include "types.h"
#include "Neuron.cpp"
#include <vector>
#include <iostream>
#include <fstream>


class Net
{
    public:
        Net(const std::string &filename)
        {
            deserialize(filename);
        }

        Net(std::vector<u32> layers, f64 (*fn) (f64, bool) = &activation_fn)
        {
            layers.insert(layers.begin(), 0);
            for (u32 i = 1; i < layers.size(); i++)
            {
                std::vector<Neuron> layer;
                layer.assign(layers[i], Neuron(layers[i-1]+1, fn));
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

        void serialize(const std::string &filename) const
        {
            std::ofstream out;
            out.open(filename);

            out << Layers.size() << "\n";
            for (u32 i = 0; i < Layers.size(); i++)
            {
                out << Layers[i].size() << " ";
                for (u32 j = 0; j < Layers[i].size(); j++)
                {
                    out << Layers[i][j].getWeightCount() << " ";
                    for (u32 k = 0; k < Layers[i][j].getWeightCount(); k++)
                    {      
                        out << Layers[i][j].getWeight(k) << " ";
                    }
                }
                out << "\n";
            }

            out.close();
        }

        
        static f64 activation_fn(f64 x, bool derivative) 
        { 
            if (derivative)
                return x <= 0 ? 0 : 1; 
            else
                return x <= 0 ? 0 : x;
        } 


    private:
        std::vector< std::vector<Neuron> > Layers;
        

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

        void deserialize(const std::string &filename)
        {
            std::ifstream input;
            input.open(filename);

            u32 layers;
            input >> layers;
            for (u32 l = 0; l < layers; l++)
            {
                u32 layer_size;
                input >> layer_size;
                std::vector<Neuron> layer;

                for (u32 i = 0; i < layer_size; i++)
                {
                    u32 weight_count;
                    input >> weight_count;
                    std::vector<f64> weights;

                    for (u32 j = 0; j < weight_count; j++)
                    {
                        f64 w;
                        input >> w;
                        weights.push_back(w);
                    }

                    Neuron n(0, &activation_fn);
                    n.setWeights(weights);
                    layer.push_back(n);
                }

                Layers.push_back(layer);
            }

            input.close();
        }

};

#endif
