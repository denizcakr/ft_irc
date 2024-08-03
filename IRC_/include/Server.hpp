#pragma once
#include <iostream>
#include <string>
#include <unistd.h>
#include <map>
#include <vector>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Utilities.hpp"
#include "Exception.hpp"
#include "Replies.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Server;
class Client;

typedef int (Server::*command)(std::string& , Client&);


class Server{

    private:
        size_t                  port_number;
        const std::string       password;
        size_t                  server_fd;
        sockaddr_in             addr;
        std::vector<Client>     clients;
        char                    buffer[1024];
        int                     state;

        fd_set readFds;
        fd_set writeFds;
        fd_set readFdsSup;
        fd_set writeFdsSup;

    private:
        // create socket
        void createSocket(void);
        void serverAddrSocket(void);
        void socketListen(void) const;
        void run(void);
        int findMaxFd(void) const;
        void acceptClient();
        void readEvent();
        void writeEvent();


    public:
        Server();
        Server(size_t port_number, const std::string password);
        ~Server();

        void initCommands(void);



        std::map<std::string, command> commands;
        int Nick(std::string &cmd, Client& c);//zorunlu
        int Pass(std::string &cmd, Client& c);//zorunlu
        int Join(std::string &cmd, Client& c);//zorunlu
        int User(std::string &cmd, Client& c);//zorunlu
        int Cap(std::string &cmd, Client& c);//karsi tarafin hexchatten baglandigini gosteren sey
        int Info(std::string &cmd, Client& c);
        int Invite(std::string &cmd, Client& c);
        int Topic(std::string &cmd, Client& c);//operator
        int Privmsg(std::string &cmd, Client& c);//operator
        int Notice(std::string &cmd, Client& c);//operator
        int Part(std::string &cmd, Client& c);
        int Pong(std::string &cmd, Client& c);
        int Quit(std::string &cmd, Client& c);
        int Mode(std::string &cmd, Client& c);
        int Kick(std::string &cmd, Client& c);

};