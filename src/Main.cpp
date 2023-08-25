#include "Binds.h"
#include "Grid.h"
#include "StatsUI.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "tetris");
    window.setFramerateLimit(60);
    Grid grid;
    nora::binds.setGrid(grid);
    nora::StatsUI statsUI;
    statsUI.subscribeTo(*grid.getStats());
    sf::Clock deltaClock;
    sf::Time deltaTime;

    sf::RectangleShape m_background = sf::RectangleShape({1280, 720});
    m_background.setTexture(&nora::textures[nora::Texture::Background]);

    sf::Shader m_shader;
    m_shader.loadFromFile("resources/shaders/shader.frag", sf::Shader::Fragment);
    m_shader.setUniform("exposure", 0.75f);
    m_shader.setUniform("decay", 0.75f);
    m_shader.setUniform("density", 0.05f);
    m_shader.setUniform("weight", 0.4f);
    m_shader.setUniform("lightPositionOnScreen", sf::Vector2f(0.5f, 0.5f));
    m_shader.setUniform("myTexture", sf::Shader::CurrentTexture);
    sf::RenderStates renderState;
    renderState.shader = &m_shader;

    while (window.isOpen()) {
        deltaTime = deltaClock.restart();
        grid.update(deltaTime);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                nora::binds.keyUpdate(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                nora::binds.keyUpdate(event.key.code, false);
                break;
            default:
                break;
            }
        }

        window.clear();
        window.draw(m_background, renderState);
        window.draw(statsUI);
        window.draw(grid);
        window.display();
    }
}
