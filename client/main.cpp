#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <thread>

#include "ActionServer.h"
#include "EventClient.h"
#include "Graphics.h"
#include "Object.h"
#include "structConfig.h"

#include "Game.h"

const int fps = 30;
const float tick_duration = 1.0 / fps;

bool new_message_received = false;
std::vector<std::shared_ptr<ObjectInterface>> msg;

void getServerMessage(ActionServer *actionServer) {
    while (true) {
        msg = actionServer->getMessage();
        new_message_received = false;
//        for (auto m : msg)
//            std::cout << m->type;
    }
}

int main() {
    struct Config config;
    ActionServer actionServer;

    std::map<sf::Keyboard::Key, int> keyToCode;

    keyToCode[sf::Keyboard::W] = 0;
    keyToCode[sf::Keyboard::A] = 1;
    keyToCode[sf::Keyboard::S] = 2;
    keyToCode[sf::Keyboard::D] = 3;
    std::string score1;
    std::string score2;
    std::string time;

    actionServer.connectClient();

    sf::RenderWindow window(sf::VideoMode(config.window_width, config.window_height), "Spacy");
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(60);

    Graphics graphics(window, config, actionServer.getId() % 2 == 1);
//
    graphics.drawMenu();
    window.display();

    msg = actionServer.getMessage();
//    std::cout << "Got first server message\n";
    for (auto m : msg) {
        if (m->type == ObjectInterface::Type::PLAYER) {
            std::shared_ptr<PlayerInterface> player =
                    std::static_pointer_cast<PlayerInterface>(m);
            if (player->ID == actionServer.getId() && player->side == 1) {
                graphics.setFlipped();
                break;

                if (player->ID == actionServer.getId()) {
                    if (player->side == 1)
                        graphics.setFlipped();
                    graphics.movePlayerTo(player->position.x, player->position.y);
                } else
                    graphics.moveEnemyTo(player->position.x, player->position.y);
                break;
            }
        }
    }
    graphics.drawField();

    graphics.drawFrontWall();
    graphics.drawGates(0, 0);
    graphics.drawEnemy();
    graphics.drawPlayer();

//    std::cout << "Thread launch...\n";
    sf::Thread thread(&getServerMessage, &actionServer);
    thread.launch();
//    std::cout << "Thread launched\n";


    boost::posix_time::time_duration current_tick_duration;

    auto curr_time = boost::posix_time::microsec_clock::universal_time();
    auto last_tick = boost::posix_time::microsec_clock::universal_time();
    auto start_time = boost::posix_time::microsec_clock::universal_time();
    sf::Vector2i mousePos;

    while (window.isOpen()) {
        sf::Event event;
        mousePos = graphics.getProjectedMousePosition(sf::Mouse::getPosition(window));

        // Обработка событий окна
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed: {
                    auto key = event.key.code;

                    switch (event.key.code)
                        case sf::Keyboard::W:
                        case sf::Keyboard::A:
                        case sf::Keyboard::S:
                        case sf::Keyboard::D:
                            actionServer.sendKeyPressedAction(keyToCode[key], mousePos.x, mousePos.y);
                    break;
                    break;
                }

                case sf::Event::KeyReleased: {
                    auto key = event.key.code;

                    switch (event.key.code)
                        case sf::Keyboard::W:
                        case sf::Keyboard::A:
                        case sf::Keyboard::S:
                        case sf::Keyboard::D:
                            actionServer.sendKeyReleasedAction(keyToCode[key], mousePos.x,
                                                               mousePos.y);
                    break;
                    break;
                }

                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        auto pl_pos = graphics.getPlayerPosition();
                        actionServer.sendActionShot(
                                pl_pos.x,
                                pl_pos.y,
                                mousePos.x,
                                mousePos.y
                        );
                    }
                    break;
            } // switch
        }

        curr_time = boost::posix_time::microsec_clock::universal_time();
        current_tick_duration = curr_time - last_tick;


        if (!new_message_received && (current_tick_duration.total_milliseconds() / 1000.0) > tick_duration) {

//            std::cout << "Processing new server message\n";
            new_message_received = true;
            last_tick = curr_time;

            window.clear();
            graphics.drawField();

            for (auto m : msg) {
                switch (m->type) {
                    case ObjectInterface::Type::BULLET: {
                        std::shared_ptr<BulletInterface> bullet =
                                std::static_pointer_cast<BulletInterface>(m);

                        graphics.drawBullet(bullet->position.x, bullet->position.y, bullet->state);
                        break;
                    }

                    case ObjectInterface::Type::PLAYER: {
                        std::shared_ptr<PlayerInterface> player =
                                std::static_pointer_cast<PlayerInterface>(m);
                        if (player->ID == actionServer.getId())
                            graphics.movePlayerTo(player->position.x, player->position.y);
                        else
                            graphics.moveEnemyTo(player->position.x, player->position.y);
                        break;
                    }
                    case ObjectInterface::Type::STATS: {
                        std::shared_ptr<Statistics> stats =
                                std::static_pointer_cast<Statistics>(m);

                        //blah blah blah
                        score1 = stats->score0;
                        score2 = stats->score1;
                        time   = stats->time_remaining;
//                        std::cout << stats->time_remaining << ' '
//                                  << stats->score0 << "  FUCK FUCK FUCK "  << stats->score1 << std::endl;
                    }
                }
            }
        }

        graphics.drawPlayer();
        graphics.drawFrontWall();
        graphics.drawGates(0, 0);
        graphics.drawEnemy();
        graphics.drawScore(score1, score2, time);
        window.display();
    }
    curr_time = boost::posix_time::microsec_clock::universal_time();

    return (0);
}
