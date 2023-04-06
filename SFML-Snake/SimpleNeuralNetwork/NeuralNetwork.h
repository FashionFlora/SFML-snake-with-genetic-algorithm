//NeuralNetwork.h
#ifndef _NNETH
#define _NNETH

#include "NeuralLayer.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

class NeuralNetwork {
	int inputs;
	int outputs;
	int hiddenLayers;
	int neuronsPerHidLayer;

	std::vector<NeuralLayer> vecLayers;
public:
	NeuralNetwork(int i, int o, int h, int nph);

	// void CreateNetwork();

	std::vector<double> GetWeights() const;

	int GetNumWeights() const;

	void SetWeights(const std::vector<double> &weights);

	std::vector<double> Calculate(const std::vector<double> &inputs) const;

	inline static double Sigmoid(double activation)
	{
		return (1 / (1 + exp(-activation)));
	}
	inline static double ReLU(double activation)
	{
		return std::max(activation, 0.0);
	}


};



#endif
