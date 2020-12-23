#include "ActionServer.h"

ActionServer::ActionServer () {}

void ActionServer::sendKeyPressedAction(int keyCode, int mx, int my) {
    KeyPressedEvent event(keyCode, mx, my);
    std::shared_ptr<EventInterface> ptr = std::make_shared<KeyPressedEvent>(event);
    netClient.send_user_action(ptr);
}

void ActionServer::sendKeyReleasedAction(int keyCode, int mx, int my) {
    KeyReleasedEvent event(keyCode, mx, my);
    std::shared_ptr<EventInterface> ptr = std::make_shared<KeyReleasedEvent>(event);
    netClient.send_user_action(ptr);
}

void ActionServer::sendActionShot() {
    auto event = ShotInterface();
    std::shared_ptr<EventInterface> ptr = std::make_shared<ShotInterface>(event);

    netClient.send_user_action(ptr);
}

std::vector<std::shared_ptr<ObjectInterface>> ActionServer::getMessage(){
    return netClient.get_server_message();
}

void ActionServer::connectClient(){
    netClient.connect_to_server(addr_server, port);
}

void ActionServer::closeConnection(){
    //функция разрыва соединения
}


//bool ActionServer::checkWinner(const std::vector<std::shared_ptr<ObjectInterface>> &objects){
//    std::map<ObjectInterface::Type, std::vector<std::shared_ptr<ObjectInterface>>> group;
//
//    for (const std::shared_ptr<ObjectInterface> &obj : objects) {
//        group[obj->type].push_back(obj);
//    }
//
//    int pointOfWinner = 0;
//    int idOfWinner = 0;
//    std::vector<MapInterface> mapData;
//
//    for (std::shared_ptr<ObjectInterface> &obj : group[ObjectInterface::Type::MAP_OBJECT]) {
//        mapData.emplace_back(*std::static_pointer_cast<MapInterface>(obj));
//    }
//
//    for (auto point : mapData[0].players_pts){
//        if(point.second > pointOfWinner) {
//            pointOfWinner = point.second;
//            idOfWinner = point.first;
//        }
//    }
//
//    return idOfWinner == myId;
//
//}
