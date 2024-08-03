#include "Server.hpp"
#include "Client.hpp"

int    Server::Cap(std::string &s, Client &c) {
    if (s == "LS")
        c.isCapt = HEX;
    else if (s == "NC")
        c.isCapt = NC;
    // else if (s == "BOT")
    //     c.isCapt = BOT;
    // else
    //     return false;
    // return true;
}