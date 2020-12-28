#include "NetClient.h"
#include "PacketManager.h"

using namespace boost::asio;
using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


void NetClient::connect_to_server(std::string addr_server, int port)
{
    ip::tcp::endpoint                               ep(ip::address::from_string(addr_server), port);
    boost::shared_ptr<boost::asio::ip::tcp::socket> sock(
        new ip::tcp::socket(io_service));

    socket_ptr = sock;
    sock->connect(ep);
    char id_user[1];
    socket_ptr->read_some(buffer(id_user, 1));
    id = static_cast<int>(id_user[0]);
}


std::vector<std::shared_ptr<ObjectInterface> > NetClient::get_server_message(){
    // std::cout << "Getting server message...\n";
    ptree                   root;
    int                     size_buff = do_read_header();
    std::basic_string<char> str("", size_buff);

    socket_ptr->read_some(buffer(str, size_buff));
    std::cout << "Message received\n";
    std::cout << str << std::endl;
    std::stringstream stream(str);
    read_json(stream, root);
    return(packet_manager.packet_adaptation_client(root));
}


void NetClient::send_user_action(std::shared_ptr<EventInterface> &event)
{
    std::string buf = packet_manager.packet_handle_client(event);
    // std::cout << "[NET CLIENT] " << "Action====================" << std::endl;
    // std::cout << buf;
    // std::cout << "[NET CLIENT] " << "End of action=============" << std::endl;
    // std::cout << "[NET CLIENT INFO] " << "Size: " << std::to_string(buf.size()) << std::endl;

    socket_ptr->write_some(buffer(std::to_string(std::to_string(buf.size()).size()), 1));
    socket_ptr->write_some(buffer(std::to_string(buf.size()), 3));
    socket_ptr->write_some(buffer(buf));
}


int NetClient::do_read_header()
{
    // std::cout << "Reading size of size...\n";
    char buf[1]     = "";
    char buf2[10] = "";

    socket_ptr->read_some(buffer(buf, 1));
    std::istringstream iss1(buf, std::istringstream::in);
    int                val1;
    iss1 >> val1;
    // std::cout << "Size of size = " << val1 << std::endl;
    // std::cout << "Reading size...\n";
    socket_ptr->read_some(buffer(buf2, val1));

    std::istringstream iss(buf2, std::istringstream::in);
    int                val;
    iss >> val;
    // std::cout << "Size = " << val << std::endl;
    return(val);
}
