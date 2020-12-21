
#ifndef SPACY_ACTIONMANAGER_H
#define SPACY_ACTIONMANAGER_H

#ifndef CLIENT_ACTIONMANAGER_H
#define CLIENT_ACTIONMANAGER_H

#include <SFML/Graphics.hpp>

#include "ActionServer.h"

#include <structConfig.h>

#include <X11/Xlib.h>
#include <unistd.h>

class actionManager {

public:
    void sendMove(actionServer &action, DirectionInterface);
    void actionUser(sf::RenderWindow &window, sf::Event &, actionServer &);
    void makeIcon(sf::RenderWindow &window);
    void defineResolution(Config &);

    bool isGame = false;
};


#endif //CLIENT_ACTIONMANAGER_H


#endif //SPACY_ACTIONMANAGER_H
