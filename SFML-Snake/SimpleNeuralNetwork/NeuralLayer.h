//NeuralLayer.h
#ifndef _NLAYERH
#define _NLAYERH

#include "Node.h"
#include <vector>

class NeuralLayer {
	int nNodes;

public:
	std::vector<Node> vNodes;

	NeuralLayer(int nodes, int weightsPerNode) : nNodes(nodes) {
		for (int i = 0; i < nodes; ++i)
			vNodes.push_back(Node(weightsPerNode));
	};

	NeuralLayer(std::vector<std::vector<double>> weights) : nNodes(weights.size()) {
		for (int i = 0; i < nNodes; ++i)
			vNodes.push_back(Node(weights[i]));
	}
};


#endif
