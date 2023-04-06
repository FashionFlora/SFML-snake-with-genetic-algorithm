

#include "Population.h"

bool Population::done()
{
	

    for(int i = 0; i < snakes.size(); i++) {
        
          if (!snakes[i].dead)
          {
              return false;
         }
        
      }
      if(!bestSnake.dead) {
         return false; 
      }
      return true;
   
}
void Population::update(sf::RenderWindow *window)
{
	
	     if(!bestSnake.dead) {  //if the best snake is not dead update it, this snake is a replay of the best from the past generation
         bestSnake.look();
         bestSnake.think(-5 , window);
         bestSnake.move();
      }
      for(int i = 0; i < snakes.size(); i++) {
        if(!snakes[i].dead) {
           snakes[i].look();
           snakes[i].think(i,window);
           snakes[i].move(); 
        }
      }
	
	
	
	
}

void Population::setBestSnake()
{
	
	   float max = 0;
       int maxIndex = 0;
       for(int i = 0; i < snakes.size(); i++) {
          if(snakes[i].fitness > max) {
             max = snakes[i].fitness;
             maxIndex = i;
			 
          }
       }
       if(max > bestFitness) {
         bestFitness = max;
         bestSnake = snakes[maxIndex].cloneForReplay();
	
         bestSnakeScore = snakes[maxIndex].getSize();
		 
		
		 std::cout <<bestSnakeScore<<std::endl;
	
		 
		 
		 
	   }
	   bestSnake = bestSnake.cloneForReplay();
       
	   
	
	
}

  Game Population::selectParent() {  
      float rando = RandomFloat(0,fitnessSum);
   
      float summation = 0;
      for(int i = 0; i < snakes.size(); i++) {
         summation += snakes[i].fitness;
         if(summation > rando) {
           return snakes[i];
         }
      }
      return snakes[0];
   }























