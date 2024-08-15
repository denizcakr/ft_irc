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

/*
ERROR: A client connects to the server and joins to a channel, and sets a password to the channel
with (mode +key) but when the other client tries to join the channel with the password, with not
a password it receives an error message which is correct but with a wrong message it joins another
channel and with correct pass. it joins to the channel but both the participants cannot send message
to the channel or see each others messages !!!

1- without pass channel = WORKS*
2- no password: ERR_NEEDMOREPARAMS = WORKS*
3- wrong password: ERR_BADCHANNELKEY = Doesnt work 
(joins another channel or clients dont join the same channel with the same name)
4- correct password: RPL_JOIN = same thing as 3 also takes the key as a participant i think whether
it is correct or not.
*/

int findChannel(std::string &name, std::vector<Channel> channel){
    for(ChannelIterator it = channel.begin(); it != channel.end(); ++it){
        if(name == (*it).channel_name)
            return 1;
    }
    return 0;
}

void printChannelMembers(Channel& channel) {
    // Kanalın client listesi üzerinde klasik for döngüsü ile iterasyon yapıyoruz
    for(std::vector<Client>::const_iterator it = channel.channel_client.begin(); it != channel.channel_client.end(); ++it) {
        const Client& client = *it;
        std::cout << "Channel: " << channel.channel_name << ", User: " << client.user << ", Nickname: " << client.nick << std::endl;
    }
}

int Server::Join(std::string &cmd, Client& c)
{
    std::vector<std::string> splitResult = Utilities::splitFromFirstSpace(cmd);
    std::string ch_name, ch_key;

    if (splitResult.size() == 2) {
        ch_name = splitResult[0];
        ch_key = splitResult[1];
    }

    if(!ch_key.empty() && ch_key[ch_key.size() - 1] == '\r')
        ch_key = ch_key.substr(0, ch_key.size() - 1);

    std::cout << "CH:" << ch_name << "|ch_key:|" << ch_key << "|" << std::endl;
    std::cout << "KEY:" << ch_key << "|" << std::endl;
    
    if(c.hexOrNc == HEX)
        ch_name = cmd.substr(0, cmd.size() - 1);

    if(findChannel(ch_name, this->channels))
    {
        for(ChannelIterator it = this->channels.begin(); it != this->channels.end(); ++it)
        {
            printChannelMembers(*it);
            // std::cout << "CH:" << (*it).channel_key << "|"<< std::endl;
            // std::cout << "CHk:" << ch_key << "|" << std::endl;
            if(ch_name == (*it).channel_name)
            {
                if((*it).channel_limit != 0 && (*it).channel_client.size() >= (*it).channel_limit) {
                    Utilities::writeReply(c.cliFd, ERR_CHANNELISFULL(c.nick, ch_name));
                    return 0;
                }
                std::cout << "TEST WRONG KEY" << ch_key << std::endl;
                if(!(*it).channel_key.empty())
                {
                    std::cout << "KEY" << ch_key << "|" << std::endl;
                    if(ch_key.empty())
                    {
                        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "MODE"));
                        return 0;
                    }
                    if(ch_key != (*it).channel_key)
                    {
                        Utilities::writeReply(c.cliFd, ERR_BADCHANNELKEY(c.nick, ch_name));
                        return 0;
                    }
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
