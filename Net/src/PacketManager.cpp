#include <iostream>
#include "PacketManager.h"

std::vector<std::shared_ptr<ObjectInterface>> PacketManager::packet_adaptation_client(ptree& root) {
    //std::cout << "[Adaptation] Starting adaptation...\n";
    std::vector<std::shared_ptr<ObjectInterface>> vector;

    std::map <std::string, int> mp;
    mp["player"] = Object::Type::PLAYER;
    mp["bullet"] = Object::Type::BULLET;
    mp["map"] = Object::Type::MAP;

     for (int j = 0; j < root.get("object", 0); ++j) {
         ptree tree = root.get_child(std::to_string(j));
         //std::cout << "[Adaptation] Parsing object #" << j << " of type " << tree.get("type", "") << std::endl;
         switch (mp[tree.get("type", "")]) {
             case Object::Type::PLAYER: {
                 int id = tree.get("id", 0);
                 std::string x = tree.get("x", "");
                 std::string y = tree.get("y", "");

                 struct PlayerInterface pl(id, {stod(x), stod(y)}, {26, 26});
                 std::shared_ptr<ObjectInterface> ptr = std::make_shared<PlayerInterface>(pl);
                 vector.push_back(ptr);
                 break;
             }

             // case Object::Type::BULLET: {
             //     std::string x = tree.get("x", "");
             //     std::string y = tree.get("y", "");
             //     struct BulletInterface bi(0, {stod(x), stod(y)},0);
             //     std::shared_ptr<ObjectInterface> ptr = std::make_shared<BulletInterface>(bi);
             //     vector.push_back(ptr);
             //     break;
             // }
             // case Object::Type::MAP: {
             //     std::map<int, int> pts_player;
             //     std::string layers_count = tree.get("layers_count", "");
             //     std::string ring_radius = tree.get("ring_radius", "");
             //     std::string count_player = tree.get("count_player", "");
             //     for (int k = 0; k < std::stoi(count_player); ++k) {
             //         std::string pts = tree.get(std::to_string(k), "");
             //         pts_player.insert({k, std::stoi(pts)});
             //     }
             //     auto a = std::stoi(layers_count);
             //     auto b = std::stod(ring_radius);
             //     struct MapInterface mi(1, a, b, pts_player);
             //     std::shared_ptr<ObjectInterface> ptr = std::make_shared<MapInterface>(mi);
             //     vector.push_back(ptr);
             //
             //     break;
             // }

             default: {
                 break;
             }

         }
     }
    //std::cout << "[Adaptation] Adaptation finished.\n";
    return vector;
}

std::string PacketManager::packet_handle_client(std::shared_ptr<EventInterface>& event) {
    std::map <EventInterface::EventType, int> mp;
    mp[EventInterface::MOVE] = 1;
    mp[EventInterface::SHOT] = 2;
    mp[EventInterface::KEYPRESSED] = 3;

    ptree root;
     switch (mp[event->type]) {
         case 1: {
             auto ptr = std::static_pointer_cast<MoveInterface>(event);
             root.put("type", "move");
             root.put("direction", (int)ptr->direction);
             break;
         }
         case 2: {
             auto ptr = std::static_pointer_cast<ShotInterface>(event);
             root.put("type", "shot");
             break;
         }
         case 3: {
             auto ptr = std::static_pointer_cast<KeyPressedEvent>(event);
             root.put("type", "keypressed");
             root.put("keycode", ptr->keyCode);
             break;
         }
         default: {
             break;
         }

     }
    std::stringstream buf;
    write_json(buf, root);
    return buf.str();
}
