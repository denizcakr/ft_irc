#include "Server.hpp"

int findChannel(std::string &name, std::vector<Channel> channel){
    for(ChannelIterator it = channel.begin(); it != channel.end(); ++it){
        if(name == (*it).channel_name)
            return 1;
    }
    return 0;
}

int Server::Join(std::string &cmd, Client& c){
    (void)c;
    // std::size_t pos = cmd.find('#');
    // if (pos != std::string::npos) {
    //     ch_name = cmd;
    //     std::cout << "channel_name: " << ch_name << std::endl;
    // }

    std::string ch_name = cmd;
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
        this->channels.push_back(a);
        Utilities::writeReply(c.cliFd, RPL_JOIN(c.nick, c.ipAddr, ch_name));
        this->showRightGui(c, this->channels.back());
    }
    return 0;
    // if(findChannel())
}