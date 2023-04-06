//Game.cpp
#include "game.h"

Game::Game(int w, int h, int s) : height(h), width(w), snakeSize(s), facing(DIR::RIGHT) {

    //TODO initialize the snake (in different locations?)
	snake.clear();
    for (int i = 0; i < s; ++i) {
        snake.push_front(Point(i,height/2));
    }
    moveFruit();
}

void Game::reset(int s){
    snake.clear();
    snakeSize = s;
    for (int i = 0; i < s; ++i) {
        snake.push_front(Point(i,height/2));
    }
    facing = DIR::RIGHT;
    moveFruit();
}



void Game::moveFruit() {
    //TODO check if there is empty space
    if (snakeSize >= height * width) {
        //no more space
        return;
    }
    do {
        fruit.x = rand() % width;
        fruit.y = rand() % height;
    } while (std::find(snake.begin(), snake.end(), fruit) != snake.end());
}

bool Game::move(int dir) {
    // std::cout << dir << std::endl;
	steps++;
    Point head = snake.front();
    if (dir > DIR::RIGHT || dir < DIR::UP)
        dir = facing;

    switch (dir) {
        case DIR::UP:
            head.y -= 1;
            break;
        case DIR::LEFT:
            head.x -= 1;
            break;
        case DIR::DOWN:
            head.y += 1;
            break;
        case DIR::RIGHT:
            head.x += 1;
            break;
        default:
            return false;
    }

    // check if head is in a valid location
    if (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height) 
        return false;
    
    // ignore the tail
    if (std::find(snake.begin(), snake.end() - 1,head) != snake.end() - 1)
        return false;
    
    // valid location
    snake.push_front(head);
    if (fruit == head) {
        ++snakeSize;
		steps=0;
        moveFruit();
    } else {
        snake.pop_back();
    }

    // update facing
	if(steps>150)
	{
		dead=true;
		
	}
    facing = dir;

    return true;
}


std::vector<double> Game::getInputVector() const {
    int xymod;
    double tempx, tempy;
    bool swap;
    
    switch (facing) {
        case DIR::UP:
            xymod = 1;
            swap = false;
            break;
        case DIR::LEFT:
            xymod = 1;
            swap = true;
            break;
        case DIR::DOWN:
            xymod = -1;
            swap = false;
            break;
        case DIR::RIGHT:
            xymod = -1;
            swap = true;
            break;
    }

    std::vector<double> vals(25);
    int count = 0;
    int headx = snake.front().x;
    int heady = snake.front().y;
    // std::cout << std::endl << "|| " << headx << " " << heady << " , " << swap << " " << xymod << " ||" << std::endl;
    for (int i=-2; i<3; ++i) {
        for (int j=-2; j<3; ++j) {
            if (i==0 && j==0) continue;
            else if (i==1 && j==0) continue;

            if (!swap) {
                tempx = (headx + xymod * j);
                tempy = (heady + xymod * i);
            } else {
                tempx = (headx + xymod * i);
                tempy = (heady + -1 * xymod * j);
            }

                // std::cout << tempx << " " << tempy << " | " << j << " " << i << std::endl;
            if (tempx < 0 || tempx >= width || tempy < 0 || tempy >= height) {
                vals[count++] = -1;
            } else if (std::find(snake.begin(), snake.end(), Point(tempx,tempy)) != snake.end()) {
                vals[count++] = -0.5;
            } else if (tempx == fruit.x && tempy == fruit.y) {
                vals[count++] = 1;
            } else {
                vals[count++] = 0;
            }
        }
    }

    if (!swap) {
        tempx = (fruit.x == headx) ? 1 : 1.0 / (2*xymod * (fruit.x - headx));
        tempy = (fruit.y == heady) ? 1 : 1.0 / (2*xymod * (fruit.y - heady));
    } else {
        tempx = (fruit.y == heady) ? 1 : 1.0 / (2*xymod * (fruit.y - heady));
        tempy = (fruit.x == headx) ? 1 : 1.0 / (2*xymod * (fruit.x - headx));
    }
    vals[23] = tempx;
    vals[24] = tempy;

    return vals;
}


void Game::look()
{
	vision = getInputVector();
	
}

void Game::think(int i, sf::RenderWindow* window)
{
    outputs = nnet.Calculate(getInputVector());

    int currsize = 50;

    if (i == -5)
    {
        window->clear(BG_color);
        int counter = 0;


        for (auto s : snake)
        {

         
            part_snake.setPosition(s.x * currsize, s.y * currsize);
            part_snake.setSize(sf::Vector2f{ float(currsize),float (currsize) });

            if (counter == 0)
            {
                part_snake.setFillColor(snake_color);
            }
            else
            {
                part_snake.setFillColor(snake_color_rest);
            }

            if (counter == snake.size() - 3)
            {
                part_snake.setFillColor(sf::Color::Color(70, 115, 232, 140));

            }
            if (counter == snake.size() - 2)
            {
                part_snake.setFillColor(sf::Color::Color(70, 115, 232, 120));

            }
            if (counter == snake.size() - 1)
            {
                part_snake.setFillColor(sf::Color::Color(70, 115, 232, 100));

            }

            window->draw(part_snake);

            counter++;



        }


        sf::RectangleShape part;
        part.setPosition(fruit.x * currsize, fruit.y * currsize);
        part.setSize(sf::Vector2f{ float(currsize), float(currsize) });
        part.setFillColor(food_color);
        window->draw(part);



        window->display();


    }

}

void Game::move()
{
	
	  int facing = getFacing();
      // 3 outputs
      if (outputs[0] > outputs[1] && outputs[0] > outputs[2]) {
           ++facing; //turn left
	  }
   
      else if (outputs[2] > outputs[0] && outputs[2] > outputs[1]) {
            --facing; //turn right
     
      } //else go straight
      facing = (facing % 4 + 4) % 4;
      validMove = move(facing);
	  
	  if(validMove ==false)
	  {
		  dead=true;
		  
	  }
	  
	 
	
	
}



















