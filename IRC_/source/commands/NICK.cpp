#include "Server.hpp"
#include "Client.hpp"


int Server::Nick(std::string &s, Client &c) {
    std::cout << "New Nick " << s << " " << c.nick << std::endl;
    c.nick = s;
    std::cout << "Nick " << s << " " << c.nick << std::endl;
    return 1;

    // NICK eyms

}