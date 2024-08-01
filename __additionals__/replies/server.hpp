#pragma once

#include "unistd.h"
#include "iostream"
#include "sys/socket.h"
#include "arpa/inet.h"
#include "sys/types.h"
#include "string.h"
#include "vector"
#include "sys/select.h"
#include <map>
#include "client.hpp"

int createSocket(int portNo);

class client
{
    public:
        std::vector<std::string> messageBox;
        int cliFd;
        int port;
        std::string ipAddr;
};


class server
{
    public:
        std::vector<client> clients;
        int serverFd;
        int findMaxFd();

        typedef std::map<std::string , void(server::*)(std::string, client&)> reply_cmds;

        void JOIN(std::string &cmd, client& c);
        void INFO(std::string &cmd, client& c);
        void INVITE(std::string &cmd, client& c);
        void TOPIC(std::string &cmd, client& c);
        void PRIVMSG(std::string &cmd, client& c);
        void NOTICE(std::string &cmd, client& c);
        void NICK(std::string &cmd, client& c);
        void PART(std::string &cmd, client& c);
        void PONG(std::string &cmd, client& c);
        void QUIT(std::string &cmd, client& c);
        void MODE(std::string &cmd, client& c);
        void KICK(std::string &cmd, client& c);
};