#include <NetServer.h>
using namespace boost::asio;
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
#include <iostream>


std::vector<User> NetServer::accept_users(int                 players_count,
                                          const ObjectManager &objm)
{
    ip::tcp::acceptor acc(io_service, ip::tcp::endpoint(ip::tcp::v4(), 8001));
    int               player = 0;


    while (true)
    {
        if (player == players_count)
        {
            break;
        }
        boost::shared_ptr<boost::asio::ip::tcp::socket> user_socket(
            new ip::tcp::socket(io_service));
        users.emplace_back(objm.pick_enable_id(), user_socket);

        // Ожидание подключения пользователя. В дальшейнем сделать в отдельном
        // потоке.
        acc.accept(*users[player].sock);
        std::cout << "User #" << player << " connected\n";
        std::string str;
        str = static_cast<char>(player);
        std::cout << "Writing to user\n";
        users[player].sock->write_some(buffer(str));
        std::cout << "Message sent" << std::endl;
        player++;
    }
    std::cout << "NetServer: USER CONNECTED!" << std::endl;

    return(users);
}


void NetServer::notify_all_users(std::unordered_map<int, std::shared_ptr<Object> > &object)
{
    std::string buf = packet_manager.packet_handle_server(object);

    for (auto &item : users)
    {
        int str = buf.size();
        item.sock->write_some(
            buffer(std::to_string(std::to_string(str).size()), 1));
        item.sock->write_some(buffer(std::to_string(str), 10));
        item.sock->write_some(buffer(buf));
    }
}


std::shared_ptr<Event> NetServer::get_client_action(User &user)
{

    ptree root;
    char  buf[1024] = "";

    int size_buff = do_read_header(user);


    user.sock->read_some(buffer(buf, size_buff));
    std::string       json = std::string(buf);
    std::stringstream stream(json);

    read_json(stream, root);
    root.put("IDuser", user.get_username());
    return(packet_manager.packet_adaptation_server(root));
}


int NetServer::do_read_header(User &user)
{
    char buf0[1] = "";
    char buf[10] = "";

    user.sock->read_some(buffer(buf0, 1));
    std::istringstream iss0(buf0, std::istringstream::in);

    int val0;
    iss0 >> val0;

    user.sock->read_some(buffer(buf, val0));

    std::istringstream iss(buf, std::istringstream::in);

    int val;
    iss >> val;

    return(val);
}
