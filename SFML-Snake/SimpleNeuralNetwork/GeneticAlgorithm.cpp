#include "GeneticAlgorithm.h"



void GeneticAlgorithm::crossover(Game& g1, Game& g2) {
    double r = ((double) rand() / RAND_MAX);
    if (r > crossoverRate) return;

    std::vector<double> weights1 = g1.nnet.GetWeights();
    std::vector<double> weights2 = g2.nnet.GetWeights();

    //int cut = rand()%chromosomeLength;
    int cut = 0;
    for (size_t i=cut; i<weights1.size(); ++i) {
        std::swap(weights1[i],weights2[i]);
    }  
	g1.nnet.SetWeights(weights1);
}

void GeneticAlgorithm::mutate(Game& g) {
    std::vector<double> weights = g.nnet.GetWeights();
    for (size_t i=0; i<weights.size(); ++i) {
        double r = ((double) rand() / RAND_MAX);
        if (r < mutationRate)
            weights[i] += ((double) rand() / RAND_MAX) * 2 - 1; // -1 to 1
    }
	g.nnet.SetWeights(weights);
}

int GeneticAlgorithm::rouletteWheelSelect(  std::vector<Game>& pop, int popsize, double totalFitness) {
    double targetFitness = (double) (((double) rand() / RAND_MAX) * popsize);

    for (int i=0; i<popsize; ++i) {
        targetFitness -= pop[i].getFitness();
        if(targetFitness < 0) return i;
    }

    return popsize - 1;
}

void GeneticAlgorithm::Step(std::vector<Game>& pop) {
    std::sort(pop.begin(), pop.end());
    size_t popsize = pop.size();

    bestGenome = pop.back();

    pop.erase(pop.begin(), pop.begin() + floor(popsize * ELITISM_RATE));

 
    double totalFitness = 0;
    int reducedPopSize = pop.size();
    for (int i=0; i<reducedPopSize; ++i) {
        totalFitness += pop[i].getFitness();
    }

    while (pop.size() < popsize) {
        int g1 = rouletteWheelSelect(pop, reducedPopSize, totalFitness);
        int g2 = rouletteWheelSelect(pop, reducedPopSize, totalFitness);
        Game tempSnakeg1 =  Game(BOARD_X,BOARD_Y,INITIAL_SNAKE_SIZE);
		Game tempSnakeg2 =  Game(BOARD_X,BOARD_Y,INITIAL_SNAKE_SIZE);
		tempSnakeg1.nnet.SetWeights(pop[g1].nnet.GetWeights());
		tempSnakeg2.nnet.SetWeights(pop[g2].nnet.GetWeights());
        pop.push_back(tempSnakeg1);
        pop.push_back(tempSnakeg2);
        
        crossover(pop[pop.size()-2], pop[pop.size()-1]);
        mutate(pop[pop.size()-2]);
        mutate(pop[pop.size()-1]);
    }
    while (pop.size() > popsize) pop.pop_back();
}

