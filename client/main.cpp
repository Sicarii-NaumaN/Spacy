#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <chrono>
#include <thread>
#include <iostream>

#include "Graphics.h"
#include "structConfig.h"

int main() {
    struct Config config;
    int vx = 0;
    int vy = 0;

    int x = config.window_width/2;
    int y = config.window_height/2;

    sf::RenderWindow window(sf::VideoMode(config.window_width, config.window_height), "Spacy");
    Graphics graphics(window, config);
    window.setKeyRepeatEnabled(false);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            int defaultSpeed = 15;

            if (event.type == sf::Event::KeyPressed) {
              switch (event.key.code) {
                case sf::Keyboard::W :
                  vy = -defaultSpeed;
                break;
                case sf::Keyboard::A :
                  vx = -defaultSpeed;
                break;
                case sf::Keyboard::S :
                  vy = defaultSpeed;
                break;
                case sf::Keyboard::D :
                  vx = defaultSpeed;
                break;
              }
            }
            else if (event.type == sf::Event::KeyReleased) {
              switch (event.key.code) {
                case sf::Keyboard::W :
                  vy = (vy < 0) ? 0 : vy;
                break;
                case sf::Keyboard::S :
                  vy = (vy > 0) ? 0 : vy;
                break;
                case sf::Keyboard::D :
                  vx = (vx > 0) ? 0 : vx;
                break;
                case sf::Keyboard::A :
                  vx = (vx < 0) ? 0 : vx;
                break;
              }
            }
        }
        x += vx;
        y += vy;
        graphics.drawField();
        graphics.drawPlayer(x, y);
        graphics.drawFrontWall();
        window.display();

    }

    return 0;
}
