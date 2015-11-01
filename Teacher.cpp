#include "Net.cpp"
#include <vector>
#include <tuple>

using namespace std;

// ideals: vector of (tuples of (input, output))
Net backtrack(const vector< tuple< vector<f64>, vector<f64> >> &ideals, Net &net)
{
    // We will accumulate the deltas in a copy of the net.
    Net new_net = net;
    
    const u32 ideals_size = ideals.size();
    for (u32 i = 0; i < ideals_size; i++)
    {
        net.eval(get<0>(ideals[i]));
        
        // calculate the first layer
        vector<f64> prev_layer;
        vector<Neuron> &top_layer = net.getLayer(net.getLayerCount()-1);
        u32 layer_length = top_layer.size();
        for (u32 n = 0; n < layer_length; n++)
            prev_layer.push_back(top_layer[n].getOutput() - get<1>(ideals[i])[n]);

        for (u32 l = net.getLayerCount() - 1; l > 0; l--)
        {
            const u32 ws_per_n = net.getLayer(l-1).size();
            for (u32 n = 0; n < layer_length; n++)
            {
                for (u32 w = 0; w < ws_per_n; w++)
                {
                    new_net.getLayer(l)[n].getWeights()[w] +=
                        prev_layer[n] * net.getLayer(l)[n].getdOutput() * net.getLayer(l-1)[w].getOutput();
                }
            }

            vector<f64> next_layer;
            f64 next_layer_length = net.getLayer(l-1).size();
            for (u32 n = 0; n < next_layer_length; n++)
            {
                f64 acc = 0;
                for (u32 w = 0; w < layer_length; w++)
                    acc += prev_layer[w] * net.getLayer(l)[w].getdOutput() * net.getLayer(l)[w].getWeights()[n];

                next_layer.push_back(acc);
            }
        }
    }

    return new_net;
}

