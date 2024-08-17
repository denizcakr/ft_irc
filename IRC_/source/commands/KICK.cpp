#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"

int Server::Kick(std::string &input, Client& c)
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
    else if (input == c.nick)
    {
        Utilities::writeReply(c.cliFd, ERR_CHANOPKICK(c.nick, input[0]));
        return 0;
    }
    else
    {
        int flag = 0;
        for (ChannelIterator it = channels.begin(); it != channels.end(); ++it)
        {
            if ((*it).channel_name == input)
            {
                if (c.user != (*it)._opUser)
                {
                    Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, input[0]));
                    return 0;
                }
                for (ClientIterator it2 = (*it).channel_client.begin(); it2 != (*it).channel_client.end(); ++it2)
                {
                    flag = 1;
                    if ((*it2).nick == input)
                    {
                        std::string msg = "";
                        if (input.size() == 3)
                            msg = input[2];
                        std::cout << msg << std::endl;
                        Utilities::writeReply(it2->cliFd, RPL_KICK(it->_opUser, input[0], input[1], msg));
                        Utilities::writeReply(it2->cliFd, RPL_ENDOFNAMES(it2->nick, input[0]));
                        it->channel_client.erase(it2);
                        showRightGui(c, *it);
                        return 0;
                    }
                }
            }
        }
        if (flag == 0)
            Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.nick, input[0]));
        else if (flag == 1)
            Utilities::writeReply(c.cliFd, ": 431 " + c.nick + " " + input[0] + " : " +  input[1] + " not in this channel\r\n");
    }
    return 0;
}
