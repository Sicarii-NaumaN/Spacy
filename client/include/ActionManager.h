
#ifndef SPACY_ACTIONMANAGER_H
#define SPACY_ACTIONMANAGER_H

#include <SFML/Graphics.hpp>

#include "ActionServer.h"

#include "structConfig.h"

#include <X11/Xlib.h>
#include <unistd.h>

class ActionManager {

public:
    void actionUser(sf::RenderWindow &window, sf::Event &, ActionServer &);

    bool isGame = false;
};

#endif //SPACY_ACTIONMANAGER_H
