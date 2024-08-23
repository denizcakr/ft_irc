#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"
#include <iostream>

Channel::Channel(const std::string& channelName) : channel_name(channelName), topic_settable(false), channel_limit(0) {}
Channel::Channel(){}

Channel::~Channel() {}

std::vector<int>    Channel::getFds() const {
	std::vector<int> ret;
	for(int i = 0; i < (int) this->channel_client.size(); i++) {
		ret.push_back(this->channel_client[i].cliFd);
	}
	return(ret);
}

Channel* Server::getChannel(const std::string &name) {
	for (std::vector<Channel>::iterator it = this->channels.begin(); it != this->channels.end(); ++it) {
		//std::cout << "CHANNEL NAMEEEEE: " << (*it).channel_name << std::endl;
		if (name == it->channel_name) {
			return &(*it); //it returns the channel address
		}
	}
	return NULL;
}

bool Channel::is_member(Client& c)
{
	for (std::vector<Client>::iterator it = channel_client.begin(); it != channel_client.end(); ++it)
	{
		if (c.user == it->user)
		{
			return true;
		}
	}
	return false;
}
