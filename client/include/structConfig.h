#ifndef SPACY_STRUCTCONFIG_H
#define SPACY_STRUCTCONFIG_H
#include <SFML/Graphics.hpp>

struct Config {
    int window_width;
    int window_height;

    int field_width;
    int field_height;

    std::string textures_path;

    sf::Keyboard::Key UP;
    sf::Keyboard::Key DOWN;
    sf::Keyboard::Key LEFT;
    sf::Keyboard::Key RIGHT;

    Config(){
        window_width = 1280;
        window_height = 800;
        textures_path = "../client/textures/";

        field_height = 800;
        field_width = 1280;
    }

};

#endif //SPACY_STRUCTCONFIG_H
