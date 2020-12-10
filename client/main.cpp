#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <chrono>
#include <thread>

#include "Graphics.h"
#include "structConfig.h"

int main() {
    struct Config config;
    config.window_width = 1280;
    config.window_height = 800;
    config.textures_path = "../client/textures/";

    config.table_width_top = 200;
    config.table_width_bot = 800;
    config.table_height = 550;
    config.table_shift = 50;

    sf::RenderWindow window(sf::VideoMode(config.window_width, config.window_height), "qwe");
    Graphics graphics(window, config);
    int i = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        graphics.drawField();
        graphics.drawPlayer(config.window_width/2 - 50 + i/20, config.window_height/2 + 50 - i/20);
        window.display();
        ++i;
    }

    return 0;
}