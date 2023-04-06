//main.cpp
#include <iostream>
#include <string>
#include "game.h"

int main(int argc, char** argv) {
    Game game = Game(10,10,4);

    std::string cmdString;

    while (std::cin >> cmdString) {
        int dir = 4;
        
        switch (cmdString[0])
        {
            case 'w':
                dir = 0;
                break;
            case 'a':
                dir = 1;
                break;
            case 's':
                dir = 2;
                break;
            case 'd':
                dir = 3;
                break;

            case 'c':
            {
                std::vector<double> weights = game.getInputVector();
                int count = 0;
                for (int i=-2; i<3; ++i) {
                    for (int j=-2; j<3; ++j) {
                        if (i==0 && j==0) {
                            std::cout << "   ";
                            continue;
                        } else if (i==1 && j==0) {
                            std::cout << "   ";
                            continue; 
                        }
                        std::cout << weights[count++] << " ";
                    }
                    std::cout << std::endl;
                }
                std::cout << weights[count++] << " ";
                std::cout << weights[count++] << std::endl;
                continue;
            }
            default:
                break;
        }

        bool goodMove = game.move(dir);
        Point fruit = game.getFruit();
        Point head = game.getHead();

        std::cout << goodMove << std::endl;
        std::cout << "Fruit location: " << fruit.x << " " << fruit.y << std::endl;
        std::cout << "Head location: " << head.x << " " << head.y << std::endl;
        std::deque<Point> snake = game.getSnake();
        std::cout << "snake body:" << std::endl;
        for (const auto& p : snake) {
            std::cout << "||" << p.x << " " << p.y << "||" << std::endl;
        }
        std::cout << "Current length: " << game.getSize() << std::endl;
        
    }

    return 0;
}
