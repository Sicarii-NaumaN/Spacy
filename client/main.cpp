#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <chrono>
#include <thread>

#include "Graphics.h"

int W = 1280;
int H = 800;

int TABLE_W1 = 200;
int TABLE_W2 = 800;
int TABLE_H = 550;


int main() {
    sf::RenderWindow window(sf::VideoMode(W, H), "qwe");
    Graphics graphics(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        graphics.drawField();
        window.display();
    }

    return 0;
}