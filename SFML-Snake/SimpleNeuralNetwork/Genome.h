#ifndef _GENOMEH
#define _GENOMEH

#include <vector>

class Genome {
    std::vector<double> weights;
    double fitness;

public:
    // initialize fitness to 0
    Genome() : fitness(0) {};

    Genome(std::vector<double> w, double f) : weights(w), fitness(f) {};

    std::vector<double> &getWeights() { return weights; };

    const std::vector<double> &getWeights() const{ return weights; };

    const double getFitness() const { return fitness; };
    void setFitness(double f) { fitness = f; };

    // for sorting
    friend bool operator<(const Genome& l, const Genome& r) {
        return (l.fitness < r.fitness);
    }
};

#endif