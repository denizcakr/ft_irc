#include "Server.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"
#include "Client.hpp"
#include "Channel.hpp"

int Server::Quit(std::string &input, Client& c)
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
    ClientIterator baseIt;
    for (baseIt = clients.begin(); baseIt != clients.end(); ++baseIt) {
        if (baseIt->nick == c.nick)
            break;
    }
    if (baseIt == clients.end())
        return -1; // Client bulunamadı

    ChannelIterator itChan = channels.begin();
    while (itChan != channels.end())
    {
        ClientIterator itClient;
        for (itClient = itChan->channel_client.begin(); itClient != itChan->channel_client.end(); ++itClient) {
            if (itClient->nick == c.nick)
            {
                showRightGui(c, *itChan);
                break;
            }
        }
        if (itClient != itChan->channel_client.end()) {
            itChan->channel_client.erase(itClient);

            if (!itChan->channel_client.empty()) {
                itChan->_opUser = itChan->channel_client.front().nick;
                showRightGui(c, *itChan);
            }
            else {
                std::cout << RED << "Channel " << itChan->channel_name << " is deleted" << RESET << std::endl;
                itChan = channels.erase(itChan);
                showRightGui(c, *itChan);
                continue;
            }
        }
        ++itChan;
    }
    Utilities::writeReply(c.cliFd, RPL_QUIT(c.nick, input.c_str()));
    kickClient(baseIt);

    return 0;
}
