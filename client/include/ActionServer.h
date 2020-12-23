#ifndef SPACY_ACTIONSERVER_H
#define SPACY_ACTIONSERVER_H

#include <cmath>
#include <map>
#include <memory>

#include <cstring>
#include <ifaddrs.h>

#include <iostream>

#include "EventClient.h"
#include "NetClient.h"
#include <SFML/System.hpp>
#include <vector>

class ActionServer
{
private:
    NetClient   netClient;
    std::string addr_server = "127.0.0.1";
    int         port        = 8001;

public:
    ActionServer();
    ~ActionServer() = default;

    void connectClient();
    void closeConnection();

    void sendKeyPressedAction(int keyCode, int mx, int my);
    void sendKeyReleasedAction(int keyCode, int mx, int my);
    void sendActionShot(int ox, int oy, int mx, int my);

    std::vector<std::shared_ptr<ObjectInterface> > getMessage();
};

#endif // SPACY_ACTIONSERVER_H
