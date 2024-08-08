#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"

Channel::Channel(const std::string& channelName) : channel_name(channelName) {}

Channel::~Channel() {}

Channel* Server::getChannel(const std::string &name) {
    for (std::vector<Channel>::iterator it = this->channels.begin(); it != this->channels.end(); ++it) {
        if (name == it->channel_name) {
            return &(*it); // Kanalın adresini döndür
        }
    }
    return NULL;
}

bool Channel::is_member(Client& c)
{
    for (std::vector<Client>::iterator it = channel_client.begin(); it != channel_client.end(); ++it)
    {
        if (c.user == it->user)
        {
            return true;
        }
    }
    return false;
}
