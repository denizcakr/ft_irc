#include "Client.hpp"

Client::Client() : passCheck(0){}

Client::~Client(){}


std::string Client::getPrefix() const {
    std::string pre = this->nick;
    if(this->user.empty()){
        pre += "";
    }
    else{
        pre += "!~" + this->user;
    }
    if(this->ip.empty()){
        pre += "";
    }
    else{
        pre += "@" + this->ip;
    }
    return (pre);
}

Client& Client::operator=(Client const &copy)
{
    this->messageBox = copy.messageBox;
    this->cliFd = copy.cliFd;
    this->cliPort = copy.cliPort;
    this->ip = copy.ip;
    this->user = copy.user;
    this->nick = copy.nick;
    this->pass = copy.pass;
    return *this;
}
