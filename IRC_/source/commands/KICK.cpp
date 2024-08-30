#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include <sstream>
#include <string>

int Server::Kick(std::string &input, Client& c)
{
    std::string channelName;
    std::string userToKick;
    std::string kickReason;
    std::istringstream stream(input);
    stream >> channelName >> userToKick;
    
    // Get the rest of the input as the kick reason
    std::getline(stream, kickReason);
    if (!kickReason.empty() && kickReason[0] == ' ')
        kickReason = kickReason.substr(1);  // Remove leading space if present

    if (channelName.empty() || userToKick.empty())
    {
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "KICK"));
        return 0;
    }

    if (channelName.size() <= 1 || channelName[0] != '#') {
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "KICK"));
        return 0;
    }

    Channel *ch = getChannel(channelName);
    if (ch == NULL)
    {
        Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.nick, channelName));
        return 0;
    }

    if (ch->channel_client.empty() || c.user != ch->channel_client[0].user)
    {
        Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, channelName));
        return 0;
    }

    bool userFound = false;
    for (ClientIterator it2 = ch->channel_client.begin(); it2 != ch->channel_client.end(); ++it2)
    {
        if (it2->nick == userToKick)
        {
            userFound = true;
            // Use the provided kick reason, or "No reason given" if empty
            if(kickReason.empty()) {
                kickReason = "No reason given";
            }
            else {
                kickReason = kickReason.substr(1);
            }
            // Notify the kicked user
            Utilities::writeReply(it2->cliFd, RPL_KICK(c.nick, channelName, userToKick, kickReason));
            
            // Notify other channel members
            for (ClientIterator it3 = ch->channel_client.begin(); it3 != ch->channel_client.end(); ++it3)
            {
                if (it3->nick != userToKick) // Don't send to the kicked user again
                {
                    Utilities::writeReply(it3->cliFd, RPL_KICK(c.nick, channelName, userToKick, kickReason));
                }
            }
            
            Utilities::writeReply(it2->cliFd, RPL_ENDOFNAMES(it2->nick, channelName));
            ch->channel_client.erase(it2);
            showRightGui(c, *ch);
            break;
        }
    }

    if (!userFound)
    {
        Utilities::writeReply(c.cliFd, ERR_USERNOTINCHANNEL(c.nick, userToKick, channelName));
    }

    return 0;
}