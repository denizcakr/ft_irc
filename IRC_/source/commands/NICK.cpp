#include "Server.hpp"
#include "Client.hpp"

int Server::Nick(std::string &s, Client &c) {// NICK <nickname>
    if (s.empty()) {
        return 0;   //send message back to the client for warning "nick cannot be empty!"
    }
    c.nick = s;
    return 1;
}
