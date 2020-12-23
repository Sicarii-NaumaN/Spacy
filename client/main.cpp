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

const int fps = 30;
const float tick_duration = 1.0 / fps;

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

    boost::posix_time::time_duration current_tick_duration;
    auto last_tick = boost::posix_time::microsec_clock::universal_time();


    int i = 0;
    while (window.isOpen()) {
        auto msg = actionServer.getMessage();
        for (auto m : msg) {
          switch (m->type) {
            case Object::Type::PLAYER: {
              std::shared_ptr<PlayerInterface> player = std::static_pointer_cast<PlayerInterface>(m);
              std::cout << player->position.x << ' ' << player->position.y << std::endl;
              graphics.movePlayerTo(player->position.x, player->position.y);
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

        auto curr_time = boost::posix_time::microsec_clock::universal_time();
        current_tick_duration = curr_time - last_tick;
        if ((current_tick_duration.total_milliseconds() / 1000.0) > tick_duration) {
            last_tick = curr_time;

            graphics.drawField();
            graphics.drawPlayer();
            graphics.drawFrontWall();
            window.display();
        }
        curr_time = boost::posix_time::microsec_clock::universal_time();


    }
    return 0;
}
