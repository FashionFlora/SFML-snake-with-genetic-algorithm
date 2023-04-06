#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(int i, int o, int h, int nph) : inputs(i), outputs(o), hiddenLayers(h), neuronsPerHidLayer(nph) {
    for (int j=0; j<hiddenLayers; ++j) {
        if (j==0)
            vecLayers.push_back(NeuralLayer(neuronsPerHidLayer,inputs));
        else
            vecLayers.push_back(NeuralLayer(neuronsPerHidLayer,neuronsPerHidLayer));
    }
    if (hiddenLayers == 0) {
        vecLayers.push_back(NeuralLayer(outputs,inputs));
    } else {
        vecLayers.push_back(NeuralLayer(outputs,neuronsPerHidLayer));
    }
}

std::vector<double> NeuralNetwork::GetWeights() const {
    std::vector<double> weights;

    for (int i=0; i<hiddenLayers + 1; ++i) {
        for (size_t j=0; j<vecLayers[i].vNodes.size(); ++j) {
            for (size_t k=0; k<vecLayers[i].vNodes[j].vWeights.size(); ++k) {
                weights.push_back(vecLayers[i].vNodes[j].vWeights[k]);
            }
        }
    }

    return weights;
}

int NeuralNetwork::GetNumWeights() const {
    int count = 0;

    for (int i=0; i<hiddenLayers + 1; ++i) {
        for (size_t j=0; j<vecLayers[i].vNodes.size(); ++j) {
            count += vecLayers[i].vNodes[j].vWeights.size();
        }
    }

    return count;
}

void NeuralNetwork::SetWeights(const std::vector<double> &weights) {
    int count = 0;

    for (int i=0; i<hiddenLayers + 1; ++i) {
        for (size_t j=0; j<vecLayers[i].vNodes.size(); ++j) {
            for (size_t k=0; k<vecLayers[i].vNodes[j].vWeights.size(); ++k) {
                vecLayers[i].vNodes[j].vWeights[k] = weights[count++];
            }
        }
    }
}

std::vector<double> NeuralNetwork::Calculate(const std::vector<double> &inputs) const {
    std::vector<double> in = inputs;
    std::vector<double> out;

    for (int i=0; i<hiddenLayers + 1; ++i) {
        int count = 0;
        if (i>0) in = out;
        out.clear();

        for (size_t j=0; j<vecLayers[i].vNodes.size(); ++j) {
            double total = 0;
            for (size_t k=0; k<vecLayers[i].vNodes[j].vWeights.size(); ++k) {
                total += vecLayers[i].vNodes[j].vWeights[k] * in[count++];
            }

            if (i != hiddenLayers) {
                out.push_back(ReLU(total));
            } else {
                out.push_back(ReLU(total));
            }

            count = 0;
        }

    }

    return out;
}



