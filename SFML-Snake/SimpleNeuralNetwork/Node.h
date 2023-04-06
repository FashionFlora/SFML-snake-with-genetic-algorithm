//Node.h
#ifndef _NODEH
#define _NODEH

#include <vector>
#include <stdlib.h>

class Node {
	int nInputs;

public:
	std::vector<double> vWeights;

	// TODO add bias??
	Node(int inputs) : nInputs(inputs) {
		for (int i = 0; i < inputs; ++i)
			vWeights.push_back(((double) std::rand() / (RAND_MAX)) * 2 - 1); // random between -1 and 1
	};

	Node(std::vector<double> weights) : nInputs(weights.size()), vWeights(weights) {};

};


#endif
