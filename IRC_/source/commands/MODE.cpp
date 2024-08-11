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
// /MODE #mychannel +o alice // give operator privileges to alice
// /MODE #mychannel -o alice // take operator privileges from alice
// /MODE #mychannel +t // topic settable by channel operator only
// /MODE #mychannel -t // topic settable by anyone
// /MODE #mychannel +l 10 // set the user limit to 10
// /MODE #mychannel -l // remove the user limit
// /MODE #mychannel +k mypassword // set the channel key to "mypassword"
// /MODE #mychannel -k // remove the channel key
// /MODE #mychannel +v alice // give voice privileges to alice
// /MODE #mychannel -v alice // take voice privileges from alice

// /MODE #mychannel +n // no messages to channel from clients on the outside
// /MODE #mychannel +i // invite only
// /MODE #mychannel +s // secret
// /MODE #mychannel +p // private
// /MODE #mychannel +b *!*@*.edu // ban all users from an entire domain

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

	// for(size_t i = 0; i < cmd.size(); i++) {
	// 	std::cout << "CMD " << cmd[i] << std::endl;
	// }

	std::string channel = cmd[0];
	std::string mode = cmd[1];

	Channel *ch = getChannel(channel);
	if (ch == NULL)
	{
		Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.nick, channel));
		return 0;
	}

	if(mode[1] == 'o' || mode[1] == 'v')
	{
		if(cmd.size() < 3)
		{
			Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "MODE"));
			return 0;
		}
		std::string user = cmd[2];
		Client *cl = find_client(user);
		if (cl == NULL)
		{
			Utilities::writeReply(c.cliFd, ERR_NOSUCHNICK(c.nick));
			return 0;
		}
		if (!ch->is_member(*cl))
		{
			Utilities::writeReply(c.cliFd, ERR_USERNOTINCHANNEL(c.nick, user, channel));
			return 0;
		}
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
		if(mode[1] == 'o')
		{
			if(mode[0] == '+')
			{
				ch->oprt = cl;
				Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "+o " + user, "O"));
			}
			else if(mode[0] == '-')
			{
				ch->oprt = NULL;
				Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "-o " + user, "O"));
			}
		}
		else if(mode[1] == 'v')
		{
			if(mode[0] == '+')
			{
				ch->mode = true; //privmsg mode add!
				Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "+v " + user, "V"));
			}
			else if(mode[0] == '-')
			{
				ch->mode = false;
				Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "-v " + user, "V"));
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
					Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "MODE"));
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
				ch->channel_key = key;
				std::cout << " THIS IS THE KEY!: " << ch->channel_key << std::endl;
				Utilities::writeReply(c.cliFd, RPL_MODE(c.nick, channel, "+k " + key, "K"));
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

