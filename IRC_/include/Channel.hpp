#pragma once
#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"


class Client;
class Server;

class Channel
{
    public:
        std::string channel_name;
        std::vector<Client> channel_client;
        Channel(const std::string& channelName);
        ~Channel();
        bool is_member(Client& c);
        void sendMessageToChannel(Client& c, std::string& message, fd_set &writeFds);
        std::vector<int>    getFds() const;

};


