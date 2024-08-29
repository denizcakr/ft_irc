#pragma once
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>
#include <cerrno>
#include <cstring>

class Bot
{
	private:
		std::string Server;
		int Port; //unsidgned short??
		std::string userBot;
		std::string botNick;
		int bot_fd;
		struct sockaddr_in server_addr;
	public:
		Bot(const std::string &server, int port);
		~Bot();
		void socketBot(void);
		void execBot(void);
		void Analyzator(const std::string &message);
};