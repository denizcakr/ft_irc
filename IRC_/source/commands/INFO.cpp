#include "Server.hpp"

int Server::Info(std::string &s, Client& c){
    (void)s;

    Utilities::writeReply(c.cliFd, RPL_INFO(c.nick, Utilities::infoMessage()));
    return 1;
}