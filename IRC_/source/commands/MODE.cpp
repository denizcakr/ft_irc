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

	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ') {
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

	if(cmd.size() < 2) {
		Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "MODE"));
		return 0;
	}

	for(size_t i = 0; i < cmd.size(); i++) {
		std::cout << "CMD " << cmd[i] << std::endl;
	}

	std::string channel = cmd[0];
	std::string mode = cmd[1];

	Channel *ch = getChannel(channel);
	if (ch == NULL)
	{
		Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.nick, channel));
		return 0;
	}

	if (ch->oprt->nick != c.nick)
	{
		Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, channel));
		return 0;
	}

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
				Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "MODE"));
				return 0;
			}
			std::string user = cmd[2];
			Client *newOprt = find_client(user);
			if (newOprt == NULL)
			{
				Utilities::writeReply(c.cliFd, ERR_NOSUCHNICK(c.nick));
				return 0;
			}
			if (!ch->is_member(*newOprt))
			{
				Utilities::writeReply(c.cliFd, ERR_USERNOTINCHANNEL(c.nick, user, channel));
				return 0;
			}
			ch->oprt = newOprt;
			std::cout << "+o NEW OPERATOR: " << newOprt->user << "|" << std::endl; ///TESTER
			Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "+o " + user, "O"));
			showRightGui(*newOprt, *ch);
		}
		else if(mode[0] == '-')
		{
			std::cout << "-o CURRENT MODE OPERATOR " << ch->oprt->user << "|" << std::endl; /////TESTER
			// ch->oprt = NULL;
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

	else if(mode[1] == 't') //topic command will be redesigned!
	{
		if (ch->oprt == NULL)
		{
			Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, channel));
			return 0;
		}
		if (ch->oprt->nick != c.nick)
		{
			Utilities::writeReply(c.cliFd, ERR_CHANOPRIVSNEEDED(c.nick, channel));
			return 0;
		}
		if(mode[0] == '+')
		{
			ch->topic_settable = true;
			Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "+t", "T"));
		}
		else if(mode[0] == '-')
		{
			ch->topic_settable = false;
			Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "-t", "T"));
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
	return 0;
}
