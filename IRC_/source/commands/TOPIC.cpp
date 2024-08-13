
#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"
#include "Channel.hpp"

std::string Server::getTopic(const std::vector<std::string>& params)
{
    std::string ret = "";
    if (params.size() > 1 && params[1][0] == ':')
    {
        for (size_t i = 1; i < params.size(); ++i) {
            ret += params[i];
            ret += " ";
        }
    }
    else if (params.size() > 1)
        ret = params[1];
    return ret;
}

int Server::Topic(std::string &input, Client& c)
{
    std::vector<std::string> params = Utilities::splitStringByNewline(input);
    
    if (params.empty()) {
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "TOPIC"));
        return -1;
    }
    
    if (params.size() <= 1) {
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, params[0]));
        return -1;
    }
    
    bool flag = false;
    for (ChannelIterator it = channels.begin(); it != channels.end(); ++it) {
        if (params[0] == it->channel_name) {
            flag = true;
            if (params.size() == 1 || (params.size() > 1 && params[1] == ":")) {
                Utilities::writeReply(c.cliFd, RPL_NOTOPIC(it->_opNick, params[0]));
                return 0;
            }
            else if (params.size() >= 2) {
                if (it->_opNick != c.nick) {
                    Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, params[0]));
                    return -1;
                }
                it->topic = getTopic(params);
                std::string top = it->topic;
                if (!top.empty() && top[0] == ':') {
                    top.erase(0, 1);
                }
                std::vector<int> fds = it->getFds();
                if (!fds.empty()) {
                    Utilities::writeAllMessage(fds, RPL_TOPIC(c.nick, c.ipAddr, params[0], top));
                }
                return 0;
            }
        }
    }
    if (!flag)
        Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.nick, params[0]));

    return -1;
}
