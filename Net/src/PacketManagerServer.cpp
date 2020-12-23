#include "map"
#include <PacketManagerServer.h>


std::string PacketManagerServer::packet_handle_server(std::unordered_map<int, std::shared_ptr<Object> > &object)
{
    ptree root;

    root.put("object", object.size());

    for (int j = 0; j < object.size(); ++j)
    {
        ptree tree;

        if (object[j] != nullptr)
        {
            switch (object[j]->type)
            {
            case Object::Type::PLAYER:
            {
                auto ptr = std::static_pointer_cast<Player>(object[j]);
                tree.put("type", "player");
                tree.put("id", ptr->ID);
                tree.put("x", (int)ptr->position.x);
                tree.put("y", (int)ptr->position.y);
                tree.put("w", (int)ptr->model.width);
                tree.put("h", (int)ptr->model.height);
                root.add_child(std::to_string(j), tree);
                break;
            }

            case Object::Type::BULLET:
            {
                auto ptr = std::static_pointer_cast<Bullet>(object[j]);
                tree.put("type", "bullet");
                tree.put("x", (int)ptr->position.x);
                tree.put("y", (int)ptr->position.y);
                root.add_child(std::to_string(j), tree);
                break;
            }

            case Object::Type::MAP:
            {
                auto ptr = std::static_pointer_cast<Map>(object[j]);
                tree.put("type", "map");
                tree.put("count_player", ptr->players_pts.size());

                for (const auto &item : ptr->players_pts)
                {
                    tree.put(std::to_string(item.first), item.second);
                }

                root.add_child(std::to_string(j), tree);
                break;
            }

            default:
            {
                break;
            }
            } // switch
        }
    }

    std::stringstream buf;
    write_json(buf, root);

    return(buf.str());
} // PacketManagerServer::packet_handle_server


std::shared_ptr<Event> PacketManagerServer::packet_adaptation_server(ptree &root)
{
    std::map<std::string, int> mp;

    mp["shot"]       = 2;
    mp["keypressed"] = 3;

    std::shared_ptr<Event> ptr;

    switch (mp[root.get("type", "")])
    {
    case 2:
    {
        int  id   = root.get("IDuser", 0);
        auto shot = Shot(id);
        ptr = std::make_shared<Shot>(shot);
        break;
    }

    case 3:
    {
        int  id       = root.get("IDuser", 0);
        int  key_code = root.get("keycode", 0);
        auto keypress = KeyPressed(id, key_code);
        ptr = std::make_shared<KeyPressed>(keypress);
        break;
    }

    default:
    {
        break;
    }
    }
    return(ptr);
}
