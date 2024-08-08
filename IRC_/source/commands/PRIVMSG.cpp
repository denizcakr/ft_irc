#include <Server.hpp>
#include <Channel.hpp>
#include <Utilities.hpp>

int Server::Privmsg(std::string &input, Client& c)
{
	std::string target;
	std::string message;
	std::string::size_type pos = input.find(" ");
	//std::string::size_type is typically an unsigned integral type (like size_t), which is large enough to represent the size of any string that can be created on your system. Its exact type can vary depending on the platform and compiler.
	//It is used as the return type for functions that report the size of a string, like std::string::size() and std::string::length().
	//It is also used as the type for parameters and return values for functions that deal with string positions and substrings, like std::string::find().
	if (pos != std::string::npos)
	{
		target = input.substr(0, pos);
		message = input.substr(pos + 1);
		// message += "\n";
	}
	else
	{
		Utilities::writeReply(c.cliFd, RPL_PRIVMSG(c.user, target,"Wrong Format!")); ///????
		return 0;
	}

	for(int i = 0; target[i]; i++){
		if(target[i] == '\r')
			std::cout << "r var" << std::endl;
	}
	std::cout << "target: |" << target << "|" << std::endl;
	std::cout << "message : " << message << std::endl;

	if (target[0] == '#')
	{
		Channel *ch = getChannel(target);
	    if (ch == NULL)
	    {
	        Utilities::writeReply(c.cliFd, ERR_NOSUCHCHANNEL(c.user, target)); // nosuchchannel
	        return 0;
	    }
	    if (!ch->is_member(c)) // if the user is not a member of the channel
	    {
	        Utilities::writeReply(c.cliFd, ERR_CANNOTSENDTOCHAN(c.user));
	        return 0;
		}
	    ch->sendMessageToChannel(c, message, this->writeFds);
	}
	else
	{
		Client* cl = find_client(target);
		if (cl == NULL)
		{
			Utilities::writeReply(c.cliFd, ERR_NOSUCHNICK(c.user));
			return 0;
		}
		cl->messageBox.push_back(message);
		FD_SET(cl->cliFd, &this->writeFds);
	}
	return 0;
}
//  ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
//                      ERR_NOTOPLEVEL
//            ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
//            RPL_AWAY