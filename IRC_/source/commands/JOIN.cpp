#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"


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
		std::cout << "JOIN->Channel: " << channel.channel_name << ", User: " << client.user << ", Nickname: " << client.nick << std::endl;
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
<<<<<<< Updated upstream
	
	if(c.user.empty() && c.nick.empty()){
		Utilities::writeReply(c.cliFd, "ERROR: You must enter a username and a nickname\n");
		return 0;
	}
=======
	if(c.user.empty() && c.nick.empty())
    {
        // Utilities::writeReply(c.cliFd, ERR_NOTREGISTERED(c.user));
        Utilities::writeReply(c.cliFd, "ERROR: You must enter a username and a nickname first!\n");
        return 0;
    }
>>>>>>> Stashed changes
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
				(*it).oprt = &(*it).channel_client[0];
				std::cout << "OPERATOR: " << (*it).oprt->user << "|" << std::endl; ///TESTER
				std::cout << "CHANNEL LIMIT: " << (*it).channel_limit << "|" << std::endl; ///TESTER
				(*it).channel_client.push_back(c);
				std::string topicName = (*it).channel_name + " :" + (*it).topic;
				Utilities::writeReply(c.cliFd, RPL_JOIN(c.nick, c.ipAddr, ch_name));
				this->showRightGui(c, (*it));
				if(!(*it).topic.empty())
					Utilities::writeReply(c.cliFd, RPL_TOPIC(c.nick, c.ipAddr, (*it).channel_name, (*it).topic));
				else
					Utilities::writeReply(c.cliFd, RPL_NOTOPIC(c.nick, (*it).channel_name));
			}
		}
	}
	else {
		std::cout<< "anen" << std::endl;
		Channel a(ch_name);
		// std::cout << "USEr : " << c.user << std::endl;
		// if (a.channel_client.empty() && a.oprt == nullptr) {
		// 	a.oprt = &c;  // İlk giren kullanıcıyı operatör yap
		// 	std::cout << "First user " << c.nick << " is now the operator of channel " << a.channel_name << std::endl;
		// }
		a.oprt = &c;  // İlk giren kullanıcıyı operatör yap
		a.channel_client.push_back(c);
		std::cout << "OPERATOR: " << a.oprt->user << "|" << std::endl; ///TESTER
		this->channels.push_back(a);
		Utilities::writeReply(c.cliFd, RPL_JOIN(c.nick, c.ipAddr, ch_name));
		this->showRightGui(c, this->channels.back());
	}
	return 0;
}

