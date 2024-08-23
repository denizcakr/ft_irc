#include "Server.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"
#include "Client.hpp"
#include "Channel.hpp"

/*
ERR_NEEDMOREPARAMS (461)
ERR_NOSUCHCHANNEL (403)
ERR_NOTONCHANNEL (442)
*/

void Members(Channel& channel) //TESTER FUNCTION! CAN BE DELETED LATER
{
	for(std::vector<Client>::const_iterator it = channel.channel_client.begin(); it != channel.channel_client.end(); ++it) {
		const Client& client = *it;
		std::cout << "JOIN->Channel: " << channel.channel_name << ", User: " << client.user << ", Nickname: " << client.nick << std::endl;
	}
}

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
                        it2 = (*it).channel_client.erase(it2);///////
                        // if(it2 == (*it).channel_client.end()){}
                        //     it->oprt = &it->channel_client[0];
                        if (!it->channel_client.empty()){
                            it->oprt = &it->channel_client[0];
                            showRightGui(c, *it);

                        }
                        std::cout << RED << "Client " << c.nick << " has left channel " << input << RESET << std::endl;
                        if ((*it).channel_client.empty()) {
                            std::cout << RED << "Channel " << it->channel_name << " is deleted" << RESET << std::endl;
                            channels.erase(it);
                        }
                        Members(*it);
                        // if (!(*it).channel_client.empty())
                        // {
                        //     it->oprt = &it->channel_client.front();
                        //     showRightGui(c, *it);
                        // }
                        return 0;
                    }
                    else{
                        Utilities::writeReply(c.cliFd, ERR_NOTONCHANNEL(c.user, input));
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
