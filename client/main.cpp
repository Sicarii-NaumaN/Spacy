#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <chrono>
#include <thread>
#include <iostream>

#include "Graphics.h"
#include "structConfig.h"
#include "ActionServer.h"
#include "EventClient.h"
#include "Object.h"

#include "Game.h"

int main() {
    struct Config config;
    ActionServer actionServer;
    //ActionManager user;
    bool isGame = false;
    std::map<sf::Keyboard::Key, int> keyToCode;
    keyToCode[sf::Keyboard::W] = 0;
    keyToCode[sf::Keyboard::A] = 1;
    keyToCode[sf::Keyboard::S] = 2;
    keyToCode[sf::Keyboard::D] = 3;


    actionServer.connectClient();

    sf::RenderWindow window(sf::VideoMode(config.window_width, config.window_height), "Spacy");
    Graphics graphics(window, config);

    //graphics.movePlayerTo(x, y);

    Game game(2);

    window.setKeyRepeatEnabled(false);

    int i = 0;
    while (window.isOpen()) {
        auto msg = actionServer.getMessage();
        for (auto m : msg) {
          switch (m->type) {
            case Object::Type::PLAYER: {
              std::cout << "Got player data\n";
              break;
            }
          }
        }

        sf::Event event;
        while (window.pollEvent(event)) {
            sf::Vector2 mousePos = sf::Mouse::getPosition(window);

            switch (event.type) {
              case sf::Event::Closed:
                window.close();
                break;

              case sf::Event::KeyPressed: {
                auto key = event.key.code;
                switch (event.key.code) {
                    case sf::Keyboard::W :
                    case sf::Keyboard::A :
                    case sf::Keyboard::S :
                    case sf::Keyboard::D :
                        actionServer.sendKeyPressedAction(keyToCode[key], mousePos.x, mousePos.y);
                        break;
                }
                break;
              }
              case sf::Event::KeyReleased: {
                auto key = event.key.code;
                switch (event.key.code) {
                    case sf::Keyboard::W :
                    case sf::Keyboard::A :
                    case sf::Keyboard::S :
                    case sf::Keyboard::D :
                        actionServer.sendKeyReleasedAction(keyToCode[key], mousePos.x, mousePos.y);
                        break;
                }
                break;
              }
            }
        }
        graphics.drawField();
        graphics.drawPlayer();
        // i += 10;
        // graphics.drawBullet(240, 600 - i);
        graphics.drawFrontWall();
        window.display();
    }
    return 0;
}
