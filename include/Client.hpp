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
        int cliPort;
        char ipAddr[INET_ADDRSTRLEN];

        int hexOrNc;
        
        std::string ip;
        std::string user;
        std::string nick;
        std::string pass;

        int         isCapt;

        Client();
        ~Client();

};