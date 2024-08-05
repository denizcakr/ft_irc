#include <Server.hpp>
#include <Channel.hpp>

int Server::Privmsg(std::string &input, Client& c)
{
	(void) c; //
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
		message += "\n";
	}
	else
	{
		//c.send_reply(ERR_NORECIPIENT, c.get_nick());				//send reply !!!
		return 0;
	}

	// if (target[0] == '#')
	// {
	//     Channel *ch = find_channel(target);
	//     if (ch == NULL)
	//     {
	//         c.send_reply(ERR_NOSUCHNICK, c.get_nick());
	//         return 0;
	//     }
	//     if (!ch->is_member(c.get_nick()))
	//     {
	//         c.send_reply(ERR_CANNOTSENDTOCHAN, c.get_nick());
	//         return 0;
	//     }
	//     ch->sendMessageToChannel(c.get_nick(), message);
	//}
	//else
	{
		Client* cl = find_client(target);
		if (cl == NULL)
		{
			//c.send_reply(ERR_NOSUCHNICK, c.get_nick());
			return 0;
		}
		cl->messageBox.push_back(message);
		FD_SET(cl->cliFd, &this->writeFds);
	}
	return 0;
}