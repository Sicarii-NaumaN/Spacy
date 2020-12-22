#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <chrono>
#include <thread>
#include <iostream>

#include "Graphics.h"
#include "structConfig.h"
#include "ActionManager.h"
#include "ActionServer.h"
#include "EventClient.h"

int main() {
    struct Config config;
    //ActionServer actionServer;
    //ActionManager user;
    bool isGame = false;

    int defaultSpeed = 15;

    int vx = 0;
    int vy = 0;

    int x = config.window_width / 2;
    int y = config.window_height / 2 - 150;

    //actionServer.connectClient();

    sf::RenderWindow window(sf::VideoMode(config.window_width, config.window_height), "Spacy");
    Graphics graphics(window, config);

    graphics.movePlayerTo(x, y);

    window.setKeyRepeatEnabled(false);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
              case sf::Event::Closed:
                window.close();
                break;

              case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::W :
                        vy = -defaultSpeed;
                        //actionServer.sendActionMove(UP);
                        break;
                    case sf::Keyboard::A :
                        vx = -defaultSpeed;
                        //actionServer.sendActionMove(LEFT);
                        break;
                    case sf::Keyboard::S :
                        vy = defaultSpeed;
                        //actionServer.sendActionMove(DOWN);
                        break;
                    case sf::Keyboard::D :
                        vx = defaultSpeed;
                        //actionServer.sendActionMove(RIGHT);
                        break;
                }
                break;
              case sf::Event::KeyReleased:
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
                break;
            }
        }
        graphics.movePlayer(vx, vy);
        graphics.drawField();
        graphics.drawPlayer();
        graphics.drawFrontWall();
        window.display();
    }
    return 0;
}
