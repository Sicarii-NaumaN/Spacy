#ifndef SPACY_STRUCTCONFIG_H
#define SPACY_STRUCTCONFIG_H
#include <SFML/Graphics.hpp>

//int W = 1280;
//int H = 800;
//int TABLE_W1 = 200;
//int TABLE_W2 = 800;
//int TABLE_H = 550;

struct Config {
    int window_width;
    int window_height;

    int table_width_top;
    int table_width_bot;
    int table_height;
    int table_shift;

    int field_width;
    int field_height;

    std::string textures_path;

    sf::Keyboard::Key UP;
    sf::Keyboard::Key DOWN;
    sf::Keyboard::Key LEFT;
    sf::Keyboard::Key RIGHT;
};

#endif //SPACY_STRUCTCONFIG_H
