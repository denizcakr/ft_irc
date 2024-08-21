/* #include "Server.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"
#include "Client.hpp"
#include "Channel.hpp"

void printChannelMembers(Channel& channel) //TESTER FUNCTION! CAN BE DELETED LATER
{
	for(std::vector<Client>::const_iterator it = channel.channel_client.begin(); it != channel.channel_client.end(); ++it) {
		const Client& client = *it;
		std::cout << "Channel: " << channel.channel_name << ", User: " << client.user << ", Nickname: " << client.nick << std::endl;
	}
}
int Server::Quit(std::string &input, Client& c)
{
    std::cout << "INPUT:" << input << std::endl;
    std::cout << "CLIENT:" << c.user << std::endl;
    
    std::string channelName;
    for (int i = 0; input[i]; i++) {
    if (input[i] == ' ')
        break;
    channelName += input[i];
    }
    input = channelName;
    std::cout << "INPUT2:" << input << std::endl;
    if (input.size() <= 1 || input[1] != '#') {
        std::cout << "input[0]->" << input[0] << "|" << std::endl;
        std::cout << "DEBUG2" << input.size() << std::endl;
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, input));
        return 0;
    }
    ClientIterator baseIt;
    for (baseIt = clients.begin(); baseIt != clients.end(); ++baseIt) {
        if (baseIt->nick == c.nick)
            break;
    }
    if (baseIt == clients.end())
        return -1; // cannot find client

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
        printChannelMembers(*itChan);
        if (itClient != itChan->channel_client.end()) {
            itChan->channel_client.erase(itClient);
            printChannelMembers(*itChan);

            if (!itChan->channel_client.empty()) {
                std::cout << "operator: " << itChan->oprt->user << std::endl;
                itChan->oprt = &itChan->channel_client.front();
                std::cout << "operator after: " << itChan->oprt->user << std::endl;
                Utilities::writeReply(c.cliFd, RPL_QUIT(c.nick, input.c_str()));
                showRightGui(*(itChan->oprt), *itChan);
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
 */