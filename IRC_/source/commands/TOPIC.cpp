
#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"
#include "Channel.hpp"

int Server::Topic(std::string &input, Client& c)
{
    std::vector<std::string> params = Utilities::splitString(input, ' ');

    if (params.empty()) {
        std::cout << "params empty" << std::endl;
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "TOPIC"));
        return -1;
    }
    
    if (params.size() < 1) {
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "TOPIC"));
        return -1;
    }
    
    std::string channelName = params[0];
    std::string topicContent = "";
    if (params.size() > 1) {
        for (size_t i = 1; i < params.size(); ++i) {
            if (i > 1) topicContent += " ";
            topicContent += params[i];
        }
        if (!topicContent.empty() && topicContent[0] == ':') {
            topicContent.erase(0, 1);
        }
    }

    bool flag = false;
    for (ChannelIterator it = channels.begin(); it != channels.end(); ++it) {
        if (channelName == it->channel_name) {
            flag = true;
            if (topicContent.empty()) {
                Utilities::writeReply(c.cliFd, RPL_NOTOPIC(it->_opNick, channelName));
                return 0;
            }
            else {
                if (it->_opNick != c.nick) {
                    Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, channelName));
                    return -1;
                }
                it->topic = topicContent;
                std::vector<int> fds = it->getFds();
                if (!fds.empty()) {
                    Utilities::writeAllMessage(fds, RPL_TOPIC(c.nick, c.ipAddr, channelName, topicContent));
                }
                return 0;
            }
        }
    }
    if (!flag)
        Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.nick, channelName));

    return -1;
}

