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
    std::cout << "I'll trying to accept user\n";

    while (true)
    {
        std::cout << "Users connected now: " << player << std::endl;

        if (player == players_count)
        {
            break;
        }
        std::cout << "Connecting to user...\n";
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
    // * DEBUG * //
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
    std::cout << "[NET SERVER] "
              << "Getting client action" << std::endl;
    ptree root;
    char  buf[1024] = "";

    std::cout << "[NET SERVER] "
              << "Reading header" << std::endl;
    int size_buff = do_read_header(user);
    std::cout << "[NET SERVER] "
              << "Header ready" << std::endl;

    std::cout << "[NET SERVER] "
              << "Socket read" << std::endl;

    user.sock->read_some(buffer(buf, size_buff));
    std::cout << "[NET SERVER] "
              << "Socket read done" << std::endl;
    std::string       json = std::string(buf);
    std::stringstream stream(json);

    std::cout << "[NET SERVER] "
              << "Parsing message" << std::endl;
    std::cout << "[NET SERVER] "
              << "Message=========================" << std::endl;
    std::cout << json;
    std::cout << "[NET SERVER] "
              << "End of message==================" << std::endl;
    read_json(stream, root);
    std::cout << "[NET SERVER] "
              << "Parsing done" << std::endl;
    root.put("IDuser", user.get_username());
    return(packet_manager.packet_adaptation_server(root));
}


int NetServer::do_read_header(User &user)
{
    std::cout << "[NET SERVER] "
              << "Reading size of message" << std::endl;
    char buf[1024] = "";

    user.sock->read_some(buffer(buf, 3));
    std::cout << "[NET SERVER] "
              << "Message===================" << std::endl;
    std::cout << buf;
    std::cout << "[NET SERVER] "
              << "End of message============" << std::endl;
    std::istringstream iss(buf, std::istringstream::in);
    int                val;
    iss >> val;
    std::cout << "[NET SERVER] "
              << "Size of message: " << val << std::endl;
    return(val);
}
