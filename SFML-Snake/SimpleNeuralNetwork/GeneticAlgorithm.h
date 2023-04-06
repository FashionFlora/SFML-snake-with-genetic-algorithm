//GeneticAlgorithms.h
#ifndef _GENALGOH
#define _GENALGOH

#include "../Snake/game.h"
#include "Settings.h"

#include <vector>
#include <utility>
#include <algorithm>
#include <math.h>

class GeneticAlgorithm {
	int generation;

	int popSize;
	int chromosomeLength;
	double mutationRate;
	double crossoverRate;

	Game bestGenome =  Game(BOARD_X,BOARD_Y,INITIAL_SNAKE_SIZE);
	
	void crossover(Game& g1, Game& g2);

	void mutate(Game& g);

	int rouletteWheelSelect( std::vector<Game>& pop, int popsize, double totalFitness);
public:
	GeneticAlgorithm(int psize, double mrate, double crate) :
		popSize(psize), mutationRate(mrate), crossoverRate(crate) {};

	void Step(std::vector<Game>& pop);

	// call after running Step()
	const Game& getBestGenomeOfGeneration() {
		return bestGenome;
	}
};

#endif
