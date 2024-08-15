#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
/*
    RFC
    ERR_NEEDMOREPARAMS (461)
    ERR_NOSUCHCHANNEL (403)
    ERR_TOOMANYCHANNELS (405)
    ERR_BADCHANNELKEY (475)
    ERR_BANNEDFROMCHAN (474)
    ERR_CHANNELISFULL (471)
    ERR_INVITEONLYCHAN (473)
    ERR_BADCHANMASK (476)
    RPL_TOPIC (332)
    RPL_TOPICWHOTIME (333)
    RPL_NAMREPLY (353)
    RPL_ENDOFNAMES (366)

*/

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
    if(findChannel(ch_name, this->channels)){
        for(ChannelIterator it = this->channels.begin(); it != this->channels.end(); ++it){
            if(ch_name == (*it).channel_name){
                if((*it).is_member(c)){
                    Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED(c.user));
                    return 0;
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
}
