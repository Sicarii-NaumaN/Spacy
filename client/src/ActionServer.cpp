#include "ActionServer.h"

ActionServer::ActionServer()
{
}


void ActionServer::sendKeyPressedAction(int keyCode, int mx, int my)
{
    KeyPressedEvent                 event(keyCode, mx, my);
    std::shared_ptr<EventInterface> ptr =
        std::make_shared<KeyPressedEvent>(event);

    netClient.send_user_action(ptr);
}


void ActionServer::sendKeyReleasedAction(int keyCode, int mx, int my)
{
    KeyReleasedEvent                event(keyCode, mx, my);
    std::shared_ptr<EventInterface> ptr =
        std::make_shared<KeyReleasedEvent>(event);

    netClient.send_user_action(ptr);
}


void ActionServer::sendActionShot(int ox, int oy, int mx, int my)
{
    auto                            event = ShotInterface(ox, oy, mx, my);
    std::shared_ptr<EventInterface> ptr   = std::make_shared<ShotInterface>(event);

    netClient.send_user_action(ptr);
}


std::vector<std::shared_ptr<ObjectInterface> > ActionServer::getMessage()
{
    return(netClient.get_server_message());
}


void ActionServer::connectClient()
{
    netClient.connect_to_server(addr_server, port);
}

int ActionServer::getId() {
    return netClient.get_id();
}

void ActionServer::closeConnection()
{
    //функция разрыва соединения
}
