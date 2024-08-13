#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"

int findChannel(std::string &name, std::vector<Channel> channel){
    for(ChannelIterator it = channel.begin(); it != channel.end(); ++it){
        if(name == (*it).channel_name)
            return 1;
    }
    return 0;
}

void printChannelMembers(Channel& channel) {
    for(std::vector<Client>::iterator it = channel.channel_client.begin(); it != channel.channel_client.end(); ++it) {
        std::cout << "Channel: " << channel.channel_name << std::endl;
        std::cout << "Members: " << (*it).user << std::endl;
    }
}

int Server::Join(std::string &cmd, Client& c)
{
    std::string ch_name = Utilities::splitFromFirstSpace(cmd)[0];
    std::string chKey = Utilities::splitFromFirstSpace(cmd)[1];

    std::cout << "CH:" << ch_name << "|CHKEY:" << chKey << "|" << std::endl;
    
    if(c.hexOrNc == HEX)
        ch_name = cmd.substr(0, cmd.size() - 1);
    if(findChannel(ch_name, this->channels))
    {
        for(ChannelIterator it = this->channels.begin(); it != this->channels.end(); ++it)
        {
            printChannelMembers(*it);
            // std::cout << "CH:" << (*it).channel_key << "|"<< std::endl;
            // std::cout << "CHk:" << chKey << "|" << std::endl;
            if(ch_name == (*it).channel_name)
            {
                if((*it).channel_limit != 0 && (*it).channel_client.size() >= (*it).channel_limit) {
                    Utilities::writeReply(c.cliFd, ERR_CHANNELISFULL(c.nick, ch_name));
                    return 0;
                }
                // std::cout << "CMD SIZE" << cmd.size() << std::endl;
                // std::cout << "join key" << (*it).channel_key << std::endl;
                if(!(*it).channel_key.empty())
                {
                    if(cmd.size() < 3)
                    {
                        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "MODE"));
                        return 0;
                    }
                    if(chKey != (*it).channel_key)
                    {
                        Utilities::writeReply(c.cliFd, ERR_BADCHANNELKEY(c.nick, ch_name));
                        return 0;
                    }
                }
                (*it).channel_client.push_back(c);
                Utilities::writeReply(c.cliFd, RPL_JOIN(c.nick, c.ipAddr, ch_name));
                this->showRightGui(c, (*it));
            }
        }
    }
    else {
        Channel a(ch_name);
        a.channel_client.push_back(c);
        a.oprt = &c;
        this->channels.push_back(a);
        Utilities::writeReply(c.cliFd, RPL_JOIN(c.nick, c.ipAddr, ch_name));
        this->showRightGui(c, this->channels.back());
    }
    return 0;
    // if(findChannel())
}