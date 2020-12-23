#ifndef SPACY_ACTIONSERVER_H
#define SPACY_ACTIONSERVER_H

#include <memory>
#include <map>
#include <cmath>

#include <ifaddrs.h>
#include <cstring>

#include <iostream>

#include <vector>
#include "EventClient.h"
#include "NetClient.h"
#include <SFML/System.hpp>

class ActionServer {
private:
    NetClient netClient;
    std::string addr_server = "127.0.0.1";
    int port = 8001;
public:
    ActionServer();
    ~ActionServer() = default;

    void connectClient();
    void closeConnection();

    void sendKeyPressedAction(int keyCode, int mx, int my);
    void sendKeyReleasedAction(int keyCode, int mx, int my);
    void sendActionShot(int ox, int oy, int mx, int my);

    std::vector<std::shared_ptr<ObjectInterface>> getMessage();
};

#endif //SPACY_ACTIONSERVER_H
