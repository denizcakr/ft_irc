// #include "../include/bot.hpp"
#include "bot.hpp"

Bot::Bot(int port, std::string pass) : Port(port), Pass(pass), userBot("Bot"), botNick("Bot")
{
	std::cout << "Bot created with nick: -" << this->botNick << "-, user: -" << this->userBot << "-, password: -" << this->Pass << "-, port: -" << this->Port << "-" << std::endl;
	this->socketBot();
	this->execBot();
}

/* int Bot::getSocketFd() const
{
	return this->bot_fd;
} */

std::vector<std::string> Bot::fromFirstSpace(const std::string& input)
{
    std::vector<std::string> result;
    size_t spacePos = input.find(' ');
    std::string temp = input;
    if (input[input.size()-1] == '\n') {
        temp = input.substr(0, input.size() - 1);
    }
    if (spacePos != std::string::npos) {
        result.push_back(temp.substr(0, spacePos));
        result.push_back(temp.substr(spacePos + 1));
    } else {
        // If no space is found, the whole string is the first part, and the second part is empty.
        result.push_back(temp);
        result.push_back("");
    }
    return result;
}

void Bot::socketBot(void)
{
	this->bot_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->bot_fd < 0)
	{
		throw std::runtime_error("Bot Socket Couldnt Be Created!");
	}
	else
		std::cout << "Bot Socket is Created :)" << std::endl;
	/* if (fcntl(this->bot_fd, F_SETFL, O_NONBLOCK) < 0)
	{
		close(this->bot_fd);
		throw std::runtime_error("Failed to set socket to non-blocking mode");
	} */

	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(Port);

	if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0)
	{
		std::cerr << "Invalid IP Address!" << std::endl;
		return;
	}

	if (connect(this->bot_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1)
	{
		std::cerr << "Bot Connection To The Server Failed! Error: " << strerror(errno) << std::endl;
		throw std::runtime_error("Bot Connection To The Server Failed!");
		close(this->bot_fd);
	}
	else
		std::cout << "Bot Connection To The Server Successfull :)" << std::endl;
}

void Bot::execBot(void)
{
	int flag = 0;
	std::cout << "Bot Executing!" << std::endl;
	while (1)
	{
		std::string msgTmp;
		char buffer[1024];
		memset(buffer, 0, sizeof(buffer));
		int readed = recv(this->bot_fd, buffer, sizeof(buffer) - 1, 0);
		if(readed <= 0)
		{
			std::cerr << "Bot Disconnected!" << std::endl;
			break;
		}
		else
		{
			if(buffer[readed - 1] == '\n' || buffer[readed - 1] == '\r')
				buffer[readed - 1] = '\0';
			else
				buffer[readed] = '\0';
			msgTmp = buffer;
			std::cout << "Bot Received: " << msgTmp << std::endl;
			if(!flag)
			{
				std::string login = "PASS 123\nUSER " + this->userBot + " 0 * :Bot\n" + "NICK " + this->botNick + "\n";
				size_t ret = write(this->bot_fd, login.c_str(), login.size());
				if((int)ret < 0)
				{
					std::cerr << "Bot Login Failed!" << std::endl;
					break;
				}
				flag = 1;
			}
		}
		std::string cliMsg(msgTmp);
		if(cliMsg.empty())
			continue;
		Analyzator(cliMsg);
	}
}

void Bot::Analyzator(const std::string &message)
{
	std::string target = fromFirstSpace(message)[0];
	target = target.substr(1);
	std::cout << "Bot Target: " << target << std::endl;
	std::cout << "INCOMIN INPUT: " << message << std::endl;
	if(message.find("PING") != std::string::npos)
	{
		std::cout << "Bot Ponging!" << std::endl;
		// std::string pong = "PRIVMSG usr1 PONG \r\n";
		std::string msg = "PRIVMSG " + target + " PONG" + "\r\n";
		send(this->bot_fd, msg.c_str(), msg.size(), 0);
	}
	else if(message.find("PRIVMSG") != std::string::npos)
	{
		if(message.find("Hello") != std::string::npos)
		{
			std::string msg = "PRIVMSG " + target + " Wassup Mate!" + "\r\n";
			send(this->bot_fd, msg.c_str(), msg.size(), 0);
		}
		if(message.find("Sassy") != std::string::npos)
		{
			std::string msg = "PRIVMSG " + target + " Wadiyatalkinabeet!" + "\r\n";
			send(this->bot_fd, msg.c_str(), msg.size(), 0);
		}
		/* if(message.find("Date") != std::string::npos)
		{
			std::time_t currentTime = std::time(0);
			char* dt = std::ctime(&currentTime);
			std::string msg = "PRIVMSG " + target + (std::string)dt + "\r\n";
			send(this->bot_fd, msg.c_str(), msg.size(), 0);
		} */
		if(message.find("Bye") != std::string::npos)
		{
			std::string msg = "PRIVMSG " + target + " See ya later!" + "\r\n";
			send(this->bot_fd, msg.c_str(), msg.size(), 0);
		}
	}
}

Bot::~Bot()
{
	close(this->bot_fd);
	std::cout << "X Bot Destroyed X" << std::endl;
}