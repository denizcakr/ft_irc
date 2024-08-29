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
#include <cstdlib>

class Bot
{
	private:
		int Port; //unsidgned short??
		std::string Pass;
		std::string userBot;
		std::string botNick;
		int bot_fd;
	public:
		Bot(int port, std::string pass);
		~Bot();
		void socketBot(void);
		void execBot(void);
		void Analyzator(const std::string &message);
};