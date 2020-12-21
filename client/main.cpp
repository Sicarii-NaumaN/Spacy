#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <chrono>
#include <thread>

#include "Graphics.h"
#include "structConfig.h"

int main() {
    struct Config config;
    int dx = 0;
    int dy = 0;

    sf::RenderWindow window(sf::VideoMode(config.window_width, config.window_height), "Spacy");
    Graphics graphics(window, config);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W))) {
                dy -= 5;
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A))) {
                dx -= 5;
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
                dx += 5;
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S))) {
                dy += 5;
            }

        }
        graphics.drawField();
        graphics.drawPlayer(config.window_width/2 - 50 + dx, config.window_height/2 + 50 + dy);
        window.display();

    }

    return 0;
}