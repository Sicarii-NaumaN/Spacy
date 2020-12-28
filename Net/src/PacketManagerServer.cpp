#include "map"
#include <PacketManagerServer.h>


std::string PacketManagerServer::packet_handle_server(std::unordered_map<int, std::shared_ptr<Object> > &object) {
    ptree root;

    int size = 0;
    for (auto obj : object) {
        if (obj.second != nullptr)
            size++;
    }

    root.put("object", size);

    for (int j = 0; j < object.size(); ++j) {
        ptree tree;

        if (object[j] != nullptr) {
            switch (object[j]->type) {
                case Object::Type::PLAYER: {
                    auto ptr = std::static_pointer_cast<Player>(object[j]);
                    tree.put("type", "player");
                    tree.put("id", ptr->ID);
                    tree.put("x", (int) ptr->position.x);
                    tree.put("y", (int) ptr->position.y);
                    tree.put("side", ptr->side);
                    root.add_child(std::to_string(j), tree);
                    break;
                }

                case Object::Type::BULLET: {
                    auto ptr = std::static_pointer_cast<Bullet>(object[j]);
                    tree.put("type", "bullet");
                    tree.put("x", (int) ptr->position.x);
                    tree.put("y", (int) ptr->position.y);
                    tree.put("state", (int) ptr->state);
                    root.add_child(std::to_string(j), tree);
                    break;
                }

                case Object::Type::GAMESTATISTICS: {
                    auto ptr = std::static_pointer_cast<GameStatistics>(object[j]);
                    tree.put("type", "stat");
                    tree.put("gates1_posx", (int) ptr->gates1_posx);
                    tree.put("gates2_posx", (int) ptr->gates2_posx);
                    tree.put("team1_score", (int) ptr->team1_score);
                    tree.put("team2_score", (int) ptr->team2_score);
                    root.add_child(std::to_string(j), tree);
                    break;
                }

            } // switch
        }
    }

    std::stringstream buf;
    write_json(buf, root);

    return (buf.str());
} // PacketManagerServer::packet_handle_server


std::shared_ptr<Event> PacketManagerServer::packet_adaptation_server(ptree &root) {
    std::map<std::string, int> mp;

    mp["shot"] = 2;
    mp["keypressed"] = 3;

    std::shared_ptr<Event> ptr;

    switch (mp[root.get("type", "")]) {
        case 2: {
            int id = root.get("IDuser", 0);
            int mouse_x = root.get("mouse_x", 0);
            int mouse_y = root.get("mouse_y", 0);
            int origin_x = root.get("origin_x", 0);
            int origin_y = root.get("origin_y", 0);
            auto shot = Shot(id, mouse_x, mouse_y, origin_x, origin_y);
            ptr = std::make_shared<Shot>(shot);
            break;
        }

        case 3: {
            int id = root.get("IDuser", 0);
            int key_code = root.get("keycode", 0);
            int mouse_x = root.get("mouse_x", 0);
            int mouse_y = root.get("mouse_y", 0);
            int state = root.get("state", 0);
            auto keypress = KeyPressed(id, key_code, mouse_x, mouse_y, state);
            ptr = std::make_shared<KeyPressed>(keypress);
            break;
        }

        default: {
            break;
        }
    }
    return (ptr);
} // PacketManagerServer::packet_adaptation_server
