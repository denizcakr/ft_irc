#include "Server.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"
#include "Client.hpp"
#include "Channel.hpp"

int Server::Part(std::string &input, Client& c)
{
    std::string channelName;
    for (int i = 0; input[i]; i++) {
        if (input[i] == ' ')
            break;
        channelName += input[i];
    }
    input = channelName;
    if (input.size() <= 1 || input[0] != '#') {
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, input));
        return 0;
    }
    else if (isChannelExist(input))
    {
        for (ChannelIterator it = channels.begin(); it != channels.end(); ++it) {
            if ((*it).channel_name == input) {
                for (ClientIterator it2 = (*it).channel_client.begin(); it2 != (*it).channel_client.end(); ++it2) {
                    if ((*it2).user == c.user) {
                        Utilities::writeReply(c.cliFd, RPL_PART(c.nick, input));
                        it->channel_client.erase(it2);
                        if (!(*it).channel_client.empty())
                            (*it)._opUser = (*it).channel_client[0].nick;
                        std::cout << RED << "Client " << c.nick << " has left channel " << input << RESET << std::endl;
                        if ((*it).channel_client.empty()) {
                            std::cout << RED << "Channel " << it->channel_name << " is deleted" << RESET << std::endl;
                            channels.erase(it);
                        }
                        if (!(*it).channel_client.empty())
                        {
                            (*it)._opUser = (*it).channel_client.front().user;
                        showRightGui(c, *it);
                        }
                        return 0;
                    }
                }
                break;
            }
        }
    }
    else  
        Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.nick, input.c_str()));
    return 0;
}
