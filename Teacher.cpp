#include "Net.cpp"
#include <vector>
#include <tuple>

using namespace std;

// ideals: vector of (tuples of (input, output))
Net backtrack(const vector< tuple< vector<f64>, vector<f64> >> &ideals, Net &net)
{
    // We will directly update the weights in a copy of the net
    Net new_net = net;
    f64 speed = 0.5;
    
    const u32 ideals_size = ideals.size();
    for (u32 i = 0; i < ideals_size; i++)
    {
        net.eval(get<0>(ideals[i]));
        
        // calculate the error for the first layer
        vector<f64> prev_errors;
        u32 layer_count = net.getLayerCount();
        u32 layer_length = net.getLayer(layer_count - 1).size();
        for (u32 n = 0; n < layer_length; n++)
            prev_errors.push_back(net.getNeuron(layer_count - 1, n).getOutput() - get<1>(ideals[i])[n]);

        // loop over the next layers
        for (u32 l = layer_count - 1; l > 0; l--)
        {
            const u32 ws_per_n = net.getLayer(l-1).size() + 1; // +1 because of each neuron's bias
            for (u32 n = 0; n < layer_length; n++)
            {
                new_net.getNeuron(l, n).getWeight(0) += -speed * prev_errors[n] * net.getNeuron(l, n).getdOutput();
                for (u32 w = 1; w < ws_per_n; w++)
                {
                    new_net.getNeuron(l, n).getWeight(w) +=
                        -speed * prev_errors[n] * net.getNeuron(l, n).getdOutput() * net.getNeuron(l-1, w-1).getOutput();
                }
            }

            // calculate the error for the current layer
            vector<f64> next_errors;
            f64 next_errors_length = net.getLayer(l-1).size();
            for (u32 n = 0; n < next_errors_length; n++)
            {
                f64 acc = 0;
                for (u32 w = 0; w < layer_length; w++)
                    acc += prev_errors[w] * net.getNeuron(l, w).getdOutput() * net.getNeuron(l, w).getWeight(n);

                next_errors.push_back(acc);
            }

            prev_errors = next_errors;
            layer_length = next_errors.size();
        }

        // calculate the last layer
        const u32 ws_per_n = net.getLayer(0).size() + 1;
        for (u32 n = 0; n < layer_length; n++)
        {
            for (u32 w = 0; w < ws_per_n; w++)
            {
                new_net.getNeuron(0, n).getWeight(w) +=
                    -speed * prev_errors[n] * net.getNeuron(0, n).getdOutput() * get<0>(ideals[i])[n];
            }
        }
    }
    
    return new_net;
}

