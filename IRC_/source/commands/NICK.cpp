#include "Server.hpp"
#include "Client.hpp"

int Server::Nick(std::string &s, Client &c) {// NICK <nickname>
    if (s.empty()) {
        return 0;   //send message back to the client for warning "nick cannot be empty!"
    }
    if (c.hexOrNc == HEX)
        s = s.substr(0, s.size() - 1);
    c.nick = s;
    //std::cout << "Nick: " << c.nick << std::endl;
    return 1;
}
