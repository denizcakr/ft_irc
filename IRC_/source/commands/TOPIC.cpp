#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"
#include "Channel.hpp"

int Server::Topic(std::string &input, Client& c)
{
    std::vector<std::string> params = Utilities::splitString(input, ' ');

    if (params.size() < 1) {
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "TOPIC"));
        return -1;
    }
    
    std::string channelName = params[0];
    std::string topicContent = "";
    if (params.size() > 1) {
        topicContent = Utilities::joinStrings(params.begin() + 1, params.end(), " ");
        if (!topicContent.empty() && topicContent[0] == ':') {
            topicContent.erase(0, 1);
        }
    }

    for (ChannelIterator it = channels.begin(); it != channels.end(); ++it) {
        if (channelName == it->channel_name) {
            if (topicContent.empty()) {
                // Topic sorgulanıyor
                if (it->topic.empty()) {
                    Utilities::writeReply(c.cliFd, RPL_NOTOPIC(c.nick, channelName));
                } else {
                    Utilities::writeReply(c.cliFd, RPL_TOPIC(c.nick, c.ipAddr, channelName, it->topic));
                }
            } else {
                std::cout << "hellothere" << std::endl;
                // Topic değiştirilmek isteniyor
                if (it->_opNick != c.nick) {
                    Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, channelName));
                    return -1;
                }
                it->topic = topicContent;
                std::cout << "Topic changed to: " << it->topic << std::endl;
                std::vector<int> fds = it->getFds();
                if (!fds.empty()) {
                    Utilities::writeAllMessage(fds, RPL_TOPIC(c.nick, c.ipAddr, channelName, topicContent));
                }
            }
            return 0;
        }
    }
    
    // Kanal bulunamadı
    Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.nick, channelName));
    return -1;
}