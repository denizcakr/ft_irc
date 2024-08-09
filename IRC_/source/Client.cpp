#include "Client.hpp"

Client::Client(){}

Client::~Client(){}

Client& Client::operator=(Client const &copy)
{
    this->messageBox = copy.messageBox;
    this->cliFd = copy.cliFd;
    this->cliPort = copy.cliPort;
    // this->ipAddr = copy.ipAddr;
    this->ip = copy.ip;
    this->user = copy.user;
    this->nick = copy.nick;
    this->pass = copy.pass;
    return *this;
}
