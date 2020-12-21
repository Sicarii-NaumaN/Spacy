#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <chrono>
#include <thread>

#include "Graphics.h"
#include "structConfig.h"

int main() {
    struct Config config;
    int vx = 0;
    int vy = 0;

    int x = config.window_width/2 - 50;
    int y = config.window_height/2 + 50;

    sf::RenderWindow window(sf::VideoMode(config.window_width, config.window_height), "Spacy");
    Graphics graphics(window, config);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
              switch (event.key.code) {
                case sf::Keyboard::W :
                  vy = -5;
                break;
                case sf::Keyboard::A :
                  vx = -5;
                break;
                case sf::Keyboard::S :
                  vy = 5;
                break;
                case sf::Keyboard::D :
                  vx = 5;
                break;
              }
            }
            else if (event.type == sf::Event::KeyReleased) {
              switch (event.key.code) {
                case sf::Keyboard::W :
                case sf::Keyboard::S :
                  vy = 0;
                break;
                case sf::Keyboard::D :
                case sf::Keyboard::A :
                  vx = 0;
                break;
              }
            }


            x += vx;
            y += vy;
        }
        graphics.drawField();
        graphics.drawPlayer(x, y);
        window.display();

    }

    return 0;
}
