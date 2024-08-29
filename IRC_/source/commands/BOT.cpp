/* #include "Client.hpp"
#include "Server.hpp"

int Server::Bot(std::string &input, Client &c)
{
	if(!isUserExist(c.user))
	{
		Utilities::writeReply(c.cliFd, ERR_NOSUCHUSER(c.nick));
		return 0;
	}
	std::string msg = input;
	if(msg.empty())
	{
		Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "BOT"));
		return 0;
	}

	/* std::string fullMessage = "BOT " + msg + "\r\n";
	send(this->bot_fd, fullMessage.c_str(), fullMessage.size(), 0); */
	/* if(sended < 0)
	{
		Utilities::writeReply(c.cliFd, ERR_CANNOTSENDTOBOT(c.nick));
		return 0;
	} */
	
	std::cout << "BOT: " << msg << std::endl;
	return 0;
}
 */