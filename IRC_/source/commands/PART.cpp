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
    Channel *ch = getChannel(input);
    if (input.size() <= 1 || input[0] != '#') {
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, input));
        return 0;
    }
    else if (ch)
    {        
        for (ClientIterator it = ch->channel_client.begin(); it != ch->channel_client.end(); ++it) {
            if (c.user == (*it).user) {
                Utilities::writeReply(c.cliFd, RPL_PART(c.nick, input));
                ch->channel_client.erase(it);
                showRightGuiButBetter(c, *ch);
                if (ch->channel_client.empty()) {
                    return 0;
                }
                break;
            }
        }
    }
    else  
        Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.nick, input.c_str()));
    return 0;
}
