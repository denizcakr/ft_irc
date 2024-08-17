#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
/*
	RFC
	ERR_NEEDMOREPARAMS (461)	present
	ERR_NOSUCHCHANNEL (403)		present
	ERR_BADCHANNELKEY (475)		present
	ERR_CHANNELISFULL (471)		present
	RPL_TOPIC (332) 			will be added
	ERR_INVITEONLYCHAN (473)	
	ERR_BANNEDFROMCHAN (474)	no need
	ERR_BADCHANMASK (476)		no need
	ERR_TOOMANYCHANNELS (405)
	RPL_TOPICWHOTIME (333)
	RPL_NAMREPLY (353)
	RPL_ENDOFNAMES (366)
*/
/*
	Operators:
		1- ONLY OPERATOR CAN OP
		2- ONLY OPERATOR CAN DEOP
		3- ONLY OPERATOR CAN SET KEY OR REMOVE KEY
		4- ONLY OPERATOR CAN SET LIMIT OR REMOVE LIMIT
		5- ONLY OPERATOR CAN SET TOPIC OR REMOVE TOPIC
		6- ONLY OPERATOR CAN SET INVITEONLY MOD OR REMOVE INVITEONLY MOD / KICK
	UPDATE!!
		-> TOPIC
		-> INVITEONLY OR KICK
 */

int findChannel(std::string &name, std::vector<Channel> channel){
	for(ChannelIterator it = channel.begin(); it != channel.end(); ++it){
		if(name == (*it).channel_name)
			return 1;
	}
	return 0;
}

void printChannelMembers(Channel& channel) //TESTER FUNCTION! CAN BE DELETED LATER
{
	for(std::vector<Client>::const_iterator it = channel.channel_client.begin(); it != channel.channel_client.end(); ++it) {
		const Client& client = *it;
		std::cout << "Channel: " << channel.channel_name << ", User: " << client.user << ", Nickname: " << client.nick << std::endl;
	}
}

int Server::Join(std::string &cmd, Client& c)
{
	std::vector<std::string> splitResult = Utilities::splitFromFirstSpace(cmd);
	std::string ch_name, ch_key;

	if (splitResult.size() == 2) {
		ch_name = splitResult[0];
		ch_key = splitResult[1];
	}
	
	if(findChannel(ch_name, this->channels))
	{
		for(ChannelIterator it = this->channels.begin(); it != this->channels.end(); ++it)
		{
			printChannelMembers(*it);
			/* std::cout << "CH:" << (*it).channel_key << "|"<< std::endl;  ///TESTER
			std::cout << "CHk:" << ch_key << "|" << std::endl;  ///TESTER */
			if(ch_name == (*it).channel_name)
			{
				if((*it).is_member(c)){
					Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED(c.user));
					return 0;
				}
				if((*it).channel_limit != 0 && (*it).channel_client.size() >= (*it).channel_limit) {
					Utilities::writeReply(c.cliFd, ERR_CHANNELISFULL(c.nick, ch_name));
					return 0;
				}
				if(!(*it).channel_key.empty())
				{
					{
						if(ch_key.empty())
						{
							Utilities::writeReply(c.cliFd, ERR_BADCHANNELKEY(c.nick, ch_name));
							return 0;
						}
						if(ch_key != (*it).channel_key)
						{
							Utilities::writeReply(c.cliFd, ERR_PASSWDMISMATCH(c.nick));
							return 0;
						}
					}
				}
				std::cout << "OPERATOR: " << (*it).oprt->user << "|" << std::endl; ///TESTER
				(*it).channel_client.push_back(c);
				std::string topicName = (*it).channel_name + " :" + (*it).topic;
				Utilities::writeReply(c.cliFd, RPL_JOIN(c.nick, c.ipAddr, ch_name));
				this->showRightGui(c, (*it));
				if(!(*it).topic.empty())
				{
					Utilities::writeReply(c.cliFd, RPL_TOPIC(c.nick, c.ipAddr, (*it).channel_name, (*it).topic));
				}
			}
		}
	}
	else {
		Channel a(ch_name);
		a.channel_client.push_back(c);
		a.oprt = &c;
		this->channels.push_back(a);
		Utilities::writeReply(c.cliFd, RPL_JOIN(c.nick, c.ipAddr, ch_name));
		this->showRightGui(c, this->channels.back());
	}
	return 0;
}
