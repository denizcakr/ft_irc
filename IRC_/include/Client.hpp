#pragma once
#include <iostream>
#include <string>
#include "Server.hpp"
#include <vector>

#define HEX 1
#define NC 2

class Client
{
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

        std::string buffer;

        int passCheck;

        Client();
        ~Client();
        Client& operator=(Client const &copy);
};