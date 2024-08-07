#pragma once
#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"


class Client;

class Channel
{
    public:
        std::string channel_name;
        std::vector<Client> channel_client;
        Channel(const std::string& channelName);
        ~Channel();
        bool is_member(Client& c);
        void sendMessageToChannel(Client& c, std::string& message, fd_set &writeFds);
        // static std::vector<Channel> channels;
        // static void addChannel(const std::string& channelName);
        // static Channel* find_channel(const std::string& channelName);
};

// static void Channel::addChannel(const std::string& channelName)
// {
//     channels.push_back(Channel(channelName));
// }

