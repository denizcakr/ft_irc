#include "Server.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include <algorithm>


int Server::Quit(std::string &input, Client& c)
{
	// std::cout << "INPUT:" << input << std::endl; // :Leaving
	// std::cout << "CLIENT:" << c.user << std::endl;

	ClientIterator c_iter;
	for (c_iter = this->clients.begin(); c_iter != this->clients.end(); ++c_iter) {
		if (c_iter->nick == c.nick)
			break;
	}
	if (c_iter == this->clients.end())
		return -1;

	for(ChannelIterator it = channels.begin(); it != channels.end(); ++it)
	{
		if((*it).is_member(c))
		{
			for (std::vector<Client>::iterator client_it = (*it).channel_client.begin(); client_it != (*it).channel_client.end(); )
			{
				if (client_it->nick == c.nick)
					client_it = (*it).channel_client.erase(client_it);
				else
					++client_it;
			}
			showRightGuiButBetter(c, *it);
		}
		Utilities::printChannelMembers(*it);
	}
	Utilities::writeReply(c.cliFd, RPL_QUIT(c.nick, input.c_str()));
	kickClient(c_iter);
	return 0;
}
