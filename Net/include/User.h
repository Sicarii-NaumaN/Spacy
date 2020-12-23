#ifndef SPACY_USER_H
#define SPACY_USER_H

#include <boost/asio.hpp>
#include <utility>

class User
{
public:
    User(int ID, boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
    {
        ID_user = ID;
        sock    = std::move(socket);
    }
    ~User() = default;
    int get_username();
    bool is_connected() { return(true); }

    boost::shared_ptr<boost::asio::ip::tcp::socket> sock;

private:
    int  ID_user;
    bool status;
};

#endif // SPACY_USER_H
