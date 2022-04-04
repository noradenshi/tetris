#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include "Grid.h"
#include "Binds.h"
#include "StatsUI.h"

#pragma warning( disable : 6262 )

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "tetris");
	window.setFramerateLimit(60);
	Grid grid;
	nora::binds.setGrid(grid);
	nora::StatsUI statsUI;
	statsUI.subscribeTo(*grid.getStats());
	sf::Clock deltaClock;
	sf::Time deltaTime;

	sf::RectangleShape m_background = sf::RectangleShape({ 1280, 720 });
	m_background.setTexture(&nora::textures[nora::Texture::Background]);

	while(window.isOpen())
	{
		deltaTime = deltaClock.restart();
		grid.update(deltaTime);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.key.code == sf::Keyboard::Escape) window.close();
			switch (event.type) {
			case sf::Event::Closed: window.close(); break;
			case sf::Event::KeyPressed: nora::binds.keyUpdate(event.key.code, true); break;
			case sf::Event::KeyReleased: nora::binds.keyUpdate(event.key.code, false); break;
			}
		}

		window.clear();
		window.draw(m_background);
		window.draw(statsUI);
		window.draw(grid);
		window.display();
	}
}