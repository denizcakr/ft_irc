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
    std::string topicContent;
    if (params.size() > 1) {
        topicContent = Utilities::joinStrings(params.begin() + 1, params.end(), " ");
        std::cout << "content: " << topicContent << std::endl;
        if (!topicContent.empty() && topicContent[0] == ':') {
            topicContent.erase(0, 1);
        }
    }

    for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it) {
        if ((*it).channel_name == channelName) {
            (*it).topic = topicContent;
            std::cout <<"topic:" << it->topic << std::endl;
            if (0)
                std::cout << "topic" <<std::endl;
            else if(!topicContent.empty() && it->_opNick != c.nick)
                Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, channelName));
            std::vector<int> fds = it->getFds();
            if (!fds.empty()) {
                Utilities::writeAllMessage(fds, RPL_TOPIC(c.nick, c.ipAddr, channelName, topicContent));
            }
            // else {
            //     std::cout << "hellothere" << std::endl;
            //     // Topic değiştirilmek isteniyor
            //     if (it->_opNick != c.nick) {
            //         Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, channelName));
            //         return -1;
            //     }
            //     it->topic = topicContent;
            //     std::cout << "Topic changed to: " << it->topic << std::endl;
            // }
            // return 0;
        }
    }
    
    // Kanal bulunamadı
    Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.nick, channelName));
    return -1;
}