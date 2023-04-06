//Game.h
#include <SFML/Graphics.hpp>

#ifndef _SNAKEGAMEH
#define _SNAKEGAMEH

#include "../SimpleNeuralNetwork/Settings.h"
#include "../SimpleNeuralNetwork/NeuralNetwork.h"
#include "point.h"
#include <deque>


enum DIR {
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3
};

class Game {
    int height;
    int width;
	
    // head is at front
    std::deque<Point> snake;
    int snakeSize ;
    int facing = DIR::RIGHT;
	
	std::vector<double>vision;
	std::vector<double>outputs;
	bool validMove = true;
	int steps=0;
    Point fruit = Point(0,0);

public:
	NeuralNetwork nnet = NeuralNetwork(NUMBER_OF_INPUTS,NUMBER_OF_OUTPUTS,HIDDEN_LAYERS,HIDDEN_LAYER_SIZE);
	double fitness =0; 
	bool dead=false;
    Game(int w, int h, int s);

    bool move(int dir);

    inline Point getFruit() {
        return fruit;
    }
    inline int getSize() {
        return snakeSize;
    }
	
	void  calculateFitness() {
        fitness = (getSize() - INITIAL_SNAKE_SIZE) * (getSize() - INITIAL_SNAKE_SIZE); 
    }
	
	double  getFitness() {
        return fitness;
    }
    inline Point getHead() {
        return snake.front();
    }

    inline int getFacing() {
        return facing;
    }


    inline const std::deque<Point> &getSnake() {
        return snake;
    }
	
	   friend bool operator<(const Game& l, const Game& r) {
        return (l.fitness < r.fitness);
    }
	
	

    std::vector<double> getInputVector() const;




    void reset(int s);

  
	sf::RectangleShape part_snake;
	sf::Color food_color = sf::Color::Color(100, 100, 100);

	sf::Color snake_color = sf::Color::Color(70, 115, 232);
	sf::Color snake_color_rest = sf::Color::Color(70, 115, 232, 160);
	sf::Color BG_color = sf::Color::Color(0, 0, 0);
	void  look();
	void think(int i, sf::RenderWindow* window);
	
	Game cloneForReplay() {  //clone a version of the snake that will be used for a replay
     Game clone = Game(BOARD_X,BOARD_Y,INITIAL_SNAKE_SIZE);
	 clone.dead =false;
     clone.nnet = nnet;
     return clone;
  }
  
    Game clone() {  //clone the snake
     Game clone = Game(BOARD_X,BOARD_Y,INITIAL_SNAKE_SIZE);
     clone.nnet = nnet;
	 clone.dead=false;
     return clone;
  }
  
	void  move();
private:
    void moveFruit();

};


#endif
