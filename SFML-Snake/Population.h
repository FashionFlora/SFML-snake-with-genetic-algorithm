
#include "SimpleNeuralNetwork/GeneticAlgorithm.h"
#include "Snake/game.h"
#include "SimpleNeuralNetwork/Settings.h"
class Population {
public:

	Game game = Game(BOARD_X,BOARD_Y,INITIAL_SNAKE_SIZE);
   std::vector<Game> snakes;
   
   Game bestSnake =  Game(BOARD_X,BOARD_Y,INITIAL_SNAKE_SIZE);
   //GeneticAlgorithm ga = GeneticAlgorithm(200,0.1,0.5);
   int bestSnakeScore = 0;
   int gen = 0;
   int samebest = 0;
   float bestFitness = 0;
   float fitnessSum = 0;
   GeneticAlgorithm ga = GeneticAlgorithm(POPULATION_SIZE,MUTATION_RATE,CROSSOVER_RATE);
	

   Population(int size) {
    
      for(int i = 0; i < size; i++) {
          snakes.push_back(Game(BOARD_X,BOARD_Y,INITIAL_SNAKE_SIZE));
      }
      bestSnake = snakes[0];
  
   }

   
   bool done();
   void update(sf::RenderWindow* window);
   void setBestSnake();
   double RandomFloat(double min, double max) {
       return ((max - min) * ((double)rand() / RAND_MAX)) + min;
   }

   
   Game selectParent();
   
   void naturalSelection() {
	   setBestSnake();
	   calculateFitnessSum();
	
      ga.Step(snakes);
      gen+=1;

   }
   

   
   void calculateFitness() {  
      for(int i = 0; i < snakes.size(); i++) {
         snakes[i].calculateFitness(); 
      }
   }
   
   void calculateFitnessSum() { 
       fitnessSum = 0;
       for(int i = 0; i < snakes.size(); i++) {
         fitnessSum += snakes[i].fitness; 
      }
       
   }
};
