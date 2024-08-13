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

int Server::Join(std::string &cmd, Client& c){
    (void)c;
    std::string ch_name = cmd;
    if(c.hexOrNc == HEX) {
        ch_name = cmd.substr(0, cmd.size() - 1);
    }
    if(findChannel(ch_name, this->channels)){
        for(ChannelIterator it = this->channels.begin(); it != this->channels.end(); ++it){
            (*it).channel_client.push_back(c);
            Utilities::writeReply(c.cliFd, RPL_JOIN(c.nick, c.ipAddr, ch_name));
            this->showRightGui(c, (*it));
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
}