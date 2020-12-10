//
// Created by naum on 10.12.2020.
//

#ifndef SPACY_PACKETMANAGER_H
#define SPACY_PACKETMANAGER_H
#include <string>
#include <vector>
#include <memory>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <PlayerModel.h>


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


class PacketManager {
public:
    PacketManager() = default;
    ~PacketManager() = default;
    std::string packet_handle_client(std::shared_ptr<EventInterface>& event);
    std::vector<std::shared_ptr<ObjectInterface>> packet_adaptation_client(ptree& root);

};

#endif //SPACY_PACKETMANAGER_H
