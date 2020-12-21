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

    PointInterface myPosition;
    VectorInterface mySight;

    int myId;

    void connectClient();
    void closeConnection();

    void sendActionMove(Direction);
    void sendActionShot();
    void updatePosition(const std::vector<std::shared_ptr<ObjectInterface>> &);
    void updateSight(sf::Vector2f);

    std::vector<std::shared_ptr<ObjectInterface>> getMessage();

};

#endif //SPACY_ACTIONSERVER_H
