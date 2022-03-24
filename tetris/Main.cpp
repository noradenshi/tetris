#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include "Grid.h"
#include "StatsUI.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "tetris");
	window.setFramerateLimit(60);

	Grid grid;
	StatsUI statsUI;
	statsUI.subscribeTo(*grid.getStats());

	sf::Clock deltaClock;
	sf::Time deltaTime;

	while(window.isOpen())
	{
		deltaTime = deltaClock.restart();
		grid.update(deltaTime);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Escape: window.close();
				case sf::Keyboard::Left: grid.move(Direction::left); break;
				case sf::Keyboard::Right: grid.move(Direction::right); break;
				case sf::Keyboard::Up: grid.rotate(true); break;
				case sf::Keyboard::Down: grid.move(Direction::down); break;
				case sf::Keyboard::Z: grid.rotate(false); break;
				case sf::Keyboard::X: grid.rotate(true); break;
				}
			}
		}

		window.clear();
		window.draw(statsUI);
		window.draw(grid);
		window.display();
	}
}