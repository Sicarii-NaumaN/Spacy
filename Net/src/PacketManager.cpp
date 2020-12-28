#include "PacketManager.h"
#include <iostream>


std::vector<std::shared_ptr<ObjectInterface> > PacketManager::packet_adaptation_client(ptree &root) {
    // std::cout << "[Adaptation] Starting adaptation...\n";
    std::vector<std::shared_ptr<ObjectInterface> > vector;

    std::map<std::string, int> mp;

    mp["player"] = 0;
    mp["bullet"] = 1;
    mp["stat"]   = 2;

    for (int j = 0; j < root.get("object", 0); ++j) {
        ptree tree = root.get_child(std::to_string(j));

        // std::cout << "[Adaptation] Parsing object #" << j << " of type " <<
        // tree.get("type", "") << std::endl;
        switch (mp[tree.get("type", "")]) {
            case 0: {
                int id = tree.get("id", 0);
                int x = tree.get("x", 0);
                int y = tree.get("y", 0);
                int w = tree.get("w", 0);
                int h = tree.get("h", 0);
                int side = tree.get("side", 0);


                struct PlayerInterface pl(id, side, VectorInterface(x, y));

                std::shared_ptr<ObjectInterface> ptr =
                        std::make_shared<PlayerInterface>(pl);
                vector.push_back(ptr);
                break;
            }

            case 1: {
                int id = tree.get("id", 0);
                int x = tree.get("x", 0);
                int y = tree.get("y", 0);
                int state = tree.get("state", 0);

                struct BulletInterface bullet(id, VectorInterface(x, y), state);
                std::shared_ptr<ObjectInterface> ptr =
                        std::make_shared<BulletInterface>(bullet);
                vector.push_back(ptr);
                break;
            }
            case 2: {
                std::cout << "[Adaptation] STATS\n";

                int gates1_posx = tree.get("gates1_posx", 0);
                int gates2_posx = tree.get("gates2_posx", 0);
                int team1_score = tree.get("team1_score", 0);
                int team2_score = tree.get("team2_score", 0);

                std::cout << "[Adaptation] STATS\n" << gates1_posx << " " << gates2_posx << std::endl;

                struct GamestatisticsInterface stat(gates1_posx, gates2_posx, team1_score, team2_score);
                std::shared_ptr<ObjectInterface> ptr =
                        std::make_shared<GamestatisticsInterface>(stat);
                vector.push_back(ptr);
                break;
            }

            default : {
                break;
            }
        }
    }

    // std::cout << "[Adaptation] Adaptation finished.\n";
    return (vector);
} // PacketManager::packet_adaptation_client


std::string PacketManager::packet_handle_client(std::shared_ptr<EventInterface> &event) {
    std::map<EventInterface::EventType, int> mp;

    mp[EventInterface::SHOT] = 2;
    mp[EventInterface::KEYPRESSED] = 3;

    ptree root;

    switch (mp[event->type]) {
        case 2: {
            auto ptr = std::static_pointer_cast<ShotInterface>(event);
            root.put("type", "shot");
            root.put("origin_x", ptr->origin_x);
            root.put("origin_y", ptr->origin_y);
            root.put("mouse_x", ptr->mouse_x);
            root.put("mouse_y", ptr->mouse_y);
            break;
        }

        case 3: {
            auto ptr = std::static_pointer_cast<KeyPressedEvent>(event);
            root.put("type", "keypressed");
            root.put("keycode", ptr->keyCode);
            root.put("mouse_x", ptr->mouse_x);
            root.put("mouse_y", ptr->mouse_y);
            root.put("state", ptr->state);
            break;
        }

        default: {
            break;
        }
    }
    std::stringstream buf;
    write_json(buf, root);
    return (buf.str());
} // PacketManager::packet_handle_client
