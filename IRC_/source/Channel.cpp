#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"

Channel::Channel(const std::string& channelName) : channel_name(channelName) {}

Channel::~Channel() {}

std::vector<int>    Channel::getFds() const {
    std::vector<int> ret;
    for(int i = 0; i < (int) this->channel_client.size(); i++) {
        ret.push_back(this->channel_client[i].cliFd);
    }
    return(ret);
}

Channel* Server::getChannel(const std::string &name) {
    for (ChannelIterator it = this->channels.begin(); it != this->channels.end(); ++it) {
        if (name == it->channel_name) {
            return &(*it); // Kanalın adresini döndür
        }
    }
    return NULL;
}

bool Channel::is_member(Client& c)
{
    for (ClientIterator it = channel_client.begin(); it != channel_client.end(); ++it)
    {
        if (c.user == it->user)
        {
            return true;
        }
    }
    return false;
}

void Channel::sendMessageToChannel(Client& c, std::string& message, fd_set &writeFds)
{
    for (ClientIterator it = channel_client.begin(); it != channel_client.end(); ++it)
    {
        if (c.user != it->user)
        {
            // Utilities::writeReply(it->cliFd, RPL_PRIVMSG(c.user, channel_name, message));
            (*it).messageBox.push_back(message);
            FD_SET((*it).cliFd, &writeFds);
        }
    }
}

