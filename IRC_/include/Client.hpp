#pragma once
#include <iostream>
#include <string>
#include "Server.hpp"


#define HEX 1
#define NC 2


class Client{

    public:
        std::vector<std::string> messageBox;
        int cliFd;
        int port;
        char ipAddr[INET_ADDRSTRLEN];
        std::string ip;
        std::string user;
        std::string nick;
        std::string pass;

        Client();
        ~Client();

};