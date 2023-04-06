#include "Population.h"


#include <algorithm>


#pragma comment(lib, "User32.lib")








const  sf::Color BG_color = sf::Color::Color(0, 0, 0);






int screenwidth = 1000;
int screenheight = 1000;



int main()
{
	sf::RenderWindow window(sf::VideoMode(screenwidth, screenheight), "Not Tetris");

	sf::Event event;

	sf::Texture square, refresh, background;


	int x = 1;
	srand(time(NULL));

	sf::Font MyFont;


	if (!MyFont.loadFromFile("Fonts\\PressStart2P.ttf"))
	{
		std::cerr << "Couldn't load font" << std::endl;
	}

	srand(time(NULL));

	Population* pop = new  Population(1000);
	int highscore = 0;

	while (window.isOpen()) {

	

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
			else if (event.type = sf::Event::KeyPressed)
			{

			}
		}



			if (pop->done()) {

				highscore = pop->bestSnake.getSize();

				pop->calculateFitness();
				pop->naturalSelection();
			}
			else {
				pop->update(&window);

			}


		}
	








	return 0;
}