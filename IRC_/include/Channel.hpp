#pragma once
#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"

class Client;
class Server;

class Channel
{
	public:
		std::string channel_name;
		std::vector<Client> channel_client;
		
		bool mode;
		std::string topic;
		std::string _opUser;
		bool topic_settable; //Channel Mode Topic
		unsigned int channel_limit;
		std::string channel_key;

		Channel(const std::string& channelName);
		Channel();
		~Channel();
		bool is_member(Client& c);
		std::vector<int>    getFds() const;


};
