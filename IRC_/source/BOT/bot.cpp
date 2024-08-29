// #include "../include/bot.hpp"
#include "bot.hpp"

Bot::Bot(int port, std::string pass) : Port(port), Pass(pass), userBot("Bot"), botNick("Bot")
{
	std::cout << "Bot created with nick: " << this->botNick << " user: " << this->userBot << " Password: " << this->Pass << " port: " << this->Port << std::endl;
	this->socketBot();
	this->execBot();
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
		}
		std::string cliMsg(msgTmp);
		if(cliMsg.empty())
			continue;
		Analyzator(cliMsg);
	}
}

void Bot::Analyzator(const std::string &message)
{
	if(message.find("PING") != std::string::npos)
	{
		std::string pong = "PONG " + message.substr(5) + "\r\n";
		send(this->bot_fd, pong.c_str(), pong.size(), 0);
	}
	if(message.find("PRIVMSG") != std::string::npos)
	{
		
	}
}

Bot::~Bot()
{
	close(this->bot_fd);
	std::cout << "X Bot Destroyed X" << std::endl;
}