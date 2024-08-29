#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"

bool findChannel(std::string &name, std::vector<Channel> channel){
	for(ChannelIterator it = channel.begin(); it != channel.end(); ++it){
		if(name == it->channel_name)
			return true;
	}
	return false;
}

int Server::Join(std::string &cmd, Client& c)
{
	std::vector<std::string> splitResult = Utilities::splitFromFirstSpace(cmd);
	std::string ch_name, ch_key;

	if (splitResult.size() == 2) {
		ch_name = splitResult[0];
		ch_key = splitResult[1];
	}
	
	if(c.user.empty() && c.nick.empty()){
		Utilities::writeReply(c.cliFd, "ERROR: You must enter a username and a nickname first!\n");
		return 0;
	}

	if(!Utilities::checkChannel(ch_name)) {
		Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.getPrefix(), ch_name));
		return 0;
	}

	if(findChannel(ch_name, this->channels))
	{
		for(ChannelIterator it = this->channels.begin(); it != this->channels.end(); ++it)
		{
		
			if(ch_name == it->channel_name)
			{
				if(it->is_member(c)){
					Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED(c.user));
					return 0;
				}
				if(it->channel_limit != 0 && it->channel_client.size() >= it->channel_limit) {
					Utilities::writeReply(c.cliFd, ERR_CHANNELISFULL(c.nick, ch_name));
					return 0;
				}
				if(!it->channel_key.empty())
				{
					{
						if(ch_key.empty())
						{
							Utilities::writeReply(c.cliFd, ERR_BADCHANNELKEY(c.nick, ch_name));
							return 0;
						}
						if(ch_key != it->channel_key)
						{
							Utilities::writeReply(c.cliFd, ERR_PASSWDMISMATCH(c.nick));
							return 0;
						}
					}
				}
				it->channel_client.push_back(c);
				std::string topicName = it->channel_name + " :" + it->topic;
				Utilities::writeReply(c.cliFd, RPL_JOIN(c.nick, c.ipAddr, ch_name));
				this->showRightGui(c, *it);
				std::cout << "TOPIC :  " << it->topic << std::endl;
				std::vector<int> fds = it->getFds();
				if (!fds.empty() && !it->topic.empty()) {
					Utilities::writeAllMessage(fds, RPL_TOPIC(c.nick, c.ipAddr, it->channel_name, it->topic));
				}
				else
					Utilities::writeReply(c.cliFd, RPL_NOTOPIC(c.nick, it->channel_name));
			}
			Utilities::printChannelMembers(*it);
		}
	}
	else {
		Channel a(ch_name);
		a.channel_client.push_back(c);
		this->channels.push_back(a);
		Utilities::writeReply(c.cliFd, RPL_JOIN(c.nick, c.ipAddr, ch_name));
		this->showRightGui(c, this->channels.back());
	}
	return 0;
}
