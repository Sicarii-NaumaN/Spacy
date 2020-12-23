//
// Created by naum on 10.12.2020.
//

#ifndef SPACY_NETSERVER_H
#define SPACY_NETSERVER_H
#include <boost/asio.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <Event.h>
#include <iostream>
#include <PacketManagerServer.h>
#include <User.h>
#include <vector>

class NetServer
{
public:
    explicit NetServer(int port) {}
    ~NetServer() = default;

    std::vector<User> accept_users(int player_count, const ObjectManager &objm);

    void notify_all_users(std::unordered_map<int, std::shared_ptr<Object> > &);

    std::shared_ptr<Event> get_client_action(User &user);

    int do_read_header(User &);

private:
    int                     port
    {};
    std::vector<User>       users;
    boost::asio::io_service io_service;
    PacketManagerServer     packet_manager;
    // PacketManager qwe;
};
#endif // SPACY_NETSERVER_H
