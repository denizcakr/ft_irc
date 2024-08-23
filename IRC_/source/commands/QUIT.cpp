#include "Server.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include <algorithm>

void ChannelMembers(Channel& channel) //TESTER FUNCTION! CAN BE DELETED LATER
{

	for(std::vector<Client>::const_iterator it = channel.channel_client.begin(); it != channel.channel_client.end(); ++it) {
		const Client& client = *it;
		std::cout << "QUIT->Channel: " << channel.channel_name << ", User: " << client.user << ", Nickname: " << client.nick << std::endl;
	}
}

int Server::Quit(std::string &input, Client& c)
{
	std::cout << "INPUT:" << input << std::endl; // :Leaving
	std::cout << "CLIENT:" << c.user << std::endl;

	ClientIterator c_iter;
	for (c_iter = clients.begin(); c_iter != clients.end(); ++c_iter) {
		if (c_iter->nick == c.nick)
			break;
	}
	if (c_iter == clients.end())
		return -1; // cannot find client

	for(ChannelIterator it = channels.begin(); it != channels.end(); ++it)
	{
		if((*it).is_member(c))
		{
			std::cout << "CLIENT FOUND: " << std::endl;

			for (std::vector<Client>::iterator client_it = (*it).channel_client.begin(); client_it != (*it).channel_client.end(); )
			{
				if (client_it->nick == c.nick){
					std::cout << YELLOW << "CLIENT REMOVED: " << c.nick << RESET << std::endl;
					client_it = (*it).channel_client.erase(client_it);
				}
				else
					++client_it;
			}

			if((*it).channel_client.empty())
			{
				Utilities::writeReply(c.cliFd, RPL_QUIT(c.nick, input.c_str()));
				it = channels.erase(it);
				showRightGui(c, *it);
				return 0;
			}
			(*it).oprt = &(*it).channel_client.front();
			showRightGui(c, *it);
		}
		ChannelMembers(*it);
	}
	Utilities::writeReply(c.cliFd, RPL_QUIT(c.nick, input.c_str()));
	kickClient(c_iter);
	return 0;
}
