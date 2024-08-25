#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Replies.hpp"

//Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]
/*	o - give/take channel operator privileges;
	t - topic settable by channel operator only flag;
	l - set the user limit to channel;
	k - set a channel key (password).
 */
// /MODE #mychannel +o alice // give operator privileges to alice		+DONE
// /MODE #mychannel -o alice // take operator privileges from alice		+DONE
// /MODE #mychannel +l 10 // set the user limit to 10					+DONE
// /MODE #mychannel -l // remove the user limit							+DONE
// /MODE #mychannel +k mypassword // set the channel key to "password"	+DONE
// /MODE #mychannel -k // remove the channel key						+DONE
// /MODE #mychannel -t // topic settable by anyone						
// /MODE #mychannel +t // topic settable by channel operator only		

// /MODE #mychannel +i // invite only
// /MODE #mychannel -i // remove invite only
// /MODE #mychannel kick

int Server::Mode(std::string &input, Client& c) // input = channel +o username!
{
	std::string tmp;
	std::vector<std::string> cmd;

	int flag = 0;
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ') {
			flag++;
			if (!tmp.empty()){
				cmd.push_back(tmp);
				tmp.clear();
			}
		} else {
			tmp += input[i];
		}
	}
	if (!tmp.empty()) { // last word
		cmd.push_back(tmp);
	}

	if (flag == 0)
		return 0;
	if(cmd.size() < 2) {
		Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "MODE"));
		return 0;
	}

	for(size_t i = 0; i < cmd.size(); i++) {
		std::cout << "CMD " << cmd[i] << std::endl;
	}
	std::string channel = cmd[0];
	std::string mode = cmd[1];

	Channel *ch = NULL;
	ch = getChannel(channel);
	std::cout << "ch-> " << ch << std::endl;
	if (ch == NULL)
	{
		Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.nick, "channel"));
		return 0;
	}

	if (ch->channel_client[0].user != c.user)
	{
		Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, channel));
		return 0;
	}


	std::cout << "MODE: " << mode << std::endl; //
	if (!mode.empty())
	{
		if(mode[1] == 'o')
		{
			if (ch->oprt == NULL)
			{
				Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, channel));
				return 0;
			}
			if(mode[0] == '+')
			{
				if(cmd.size() < 3)
				{
					Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, input));
					return 0;
				}
				std::string user_nick = cmd[2];
				Client *newOprt = find_client(user_nick);
				if (newOprt == NULL)
				{
					Utilities::writeReply(c.cliFd, ERR_NOSUCHNICK(c.nick));
					return 0;
				}
				if (!ch->is_member(*newOprt))
				{
					Utilities::writeReply(c.cliFd, ERR_USERNOTINCHANNEL(c.nick, user_nick, channel));
					return 0;
				}
				// ch->oprt = newOprt;
				std::vector<Client>::iterator it= ch->channel_client.begin();
				for(; it != ch->channel_client.end(); ++it){
					if((*it).user == newOprt->user)
						break;
				}
				if(it!= ch->channel_client.end()){
					Client found_value = *it;
					
					if(it != ch->channel_client.begin()){
						//erase the foundvalue from its original position 
						ch->channel_client.erase(it);
						//insert it at the 0th index
						ch->channel_client.insert(ch->channel_client.begin(), found_value);
						ch->oprt = &ch->channel_client[0];
					}
				}

				std::cout << "+o NEW OPERATOR: " << newOprt->user << "|" << std::endl; ///TESTER
				Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "+o " + user_nick, "O"));
				showRightGui(*newOprt, *ch);
			}
			else if(mode[0] == '-')
			{
				std::cout << "-o CURRENT MODE OPERATOR " << ch->oprt->user << "|" << std::endl; /////TESTER
				for (size_t i = 0; i < ch->channel_client.size(); i++)
				{
					if (ch->channel_client[i].user != c.user)
					{
						ch->oprt = &ch->channel_client[i];
						std::cout << "AFTER -o MODE OPERATOR " << ch->oprt->user << "|" << std::endl; ///TESTER
						Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "+o " + ch->oprt->user, "O"));
						showRightGui(*(ch->oprt), *ch);
						break; //the first user which is not the operator will be the operator.
					}
				}
			}
		}

		else if(mode[1] == 't')
		{
			if (ch->oprt == NULL)
			{
				Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, channel));
				return 0;
			}
			if(mode[0] == '+')
			{
				ch->topic_settable = true;
				std::cout << "TOPIC SETTABLE: " << ch->topic_settable << std::endl; ///TESTER
				Utilities::writeReply(c.cliFd, RPL_TOPICSETTABLE(c.nick, ch->channel_name));
			}
			else if(mode[0] == '-')
			{
				ch->topic_settable = false;
				std::cout << "TOPIC SETTABLE: " << ch->topic_settable << std::endl; ///TESTER
				Utilities::writeReply(c.cliFd, RPL_TOPICNOTSETTABLE(c.nick, ch->channel_name));
			}
		}

		else if(mode[1] == 'l' || mode[1] == 'k')
		{
			if(mode[1] == 'l')
			{
				if(mode[0] == '+')
				{
					if(cmd.size() < 3)
					{
						Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.user, "MODE"));
						return 0;
					}
					std::string lmt = cmd[2];
					if(!lmt.empty())
						ch->channel_limit = atoi(lmt.c_str());
					Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "+l " + lmt, "+L"));
				}
				else if(mode[0] == '-')
				{
					ch->channel_limit = 0;
					Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "-l ", "-L"));
				}
			}
			else if(mode[1] == 'k')
			{
				if(mode[0] == '+')
				{
					if(cmd.size() < 3)
					{
						Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "MODE"));
						return 0;
					}
					std::string key = cmd[2];				
					if(!ch->channel_key.empty())
					{
						Utilities::writeReply(c.cliFd, ERR_KEYSET(c.nick, ch->channel_name));
						return 0;
					}
					if(ch->channel_key.empty())
					{
						if(!key.empty())
							ch->channel_key = key;
						std::cout << "|THIS IS THE KEY!: " << ch->channel_key << "|" << std::endl;
						Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "+k " + key, "K"));
					}
				}
				else if(mode[0] == '-')
				{
					ch->channel_key = "";
					std::cout << " THIS IS THE KEY!: " << ch->channel_key << std::endl;
					Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "-k ","-K"));
				}
			}
		}
	}
	return 0;
}
