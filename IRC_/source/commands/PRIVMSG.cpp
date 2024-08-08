#include <Server.hpp>
#include <Channel.hpp>
#include <Utilities.hpp>

//std::string::size_type is typically an unsigned integral type (like size_t), which is large enough to represent the size of any string that can be created on your system. Its exact type can vary depending on the platform and compiler.
//It is used as the return type for functions that report the size of a string, like std::string::size() and std::string::length().
//It is also used as the type for parameters and return values for functions that deal with string positions and substrings, like std::string::find().
int Server::Privmsg(std::string &input, Client& c)
{
	std::string target;
	std::string message;
	std::string::size_type pos = input.find(" ");
	if (pos != std::string::npos)
	{
		target = input.substr(0, pos);
		message = input.substr(pos + 1);
		// message += "\n";
	}
	else
	{
		Utilities::writeReply(c.cliFd, RPL_PRIVMSG(c.nick, target,"Wrong Format!")); ///????
		return 0;
	}

	if (target[0] == '#')
	{
		Channel *ch = getChannel(target);
	    if (ch == NULL)
	    {
	        Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.nick, target));
	        return 0;
	    }
	    if (!ch->is_member(c)) // if the user is not a member of the channel
	    {
	        Utilities::writeReply(c.cliFd, ERR_CANNOTSENDTOCHAN(c.nick));
	        return 0;
		}
		std::string mes = RPL_PRIVMSG(c.nick, target, message);
		sendMessageToChannel(c, mes, *ch);
	}
	else
	{
		Client* cl = find_client(target);
		if (cl == NULL)
		{
			Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, target));
			return 0;
		}
		std::string mes = RPL_PRIVMSG(c.nick, target, message);
		cl->messageBox.push_back(mes);
		FD_SET(cl->cliFd, &this->writeFds);
	}
	return 0;
}
//  ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
//                      ERR_NOTOPLEVEL
//            ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
//            RPL_AWAY