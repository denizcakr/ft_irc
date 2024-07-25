#pragma once
#include <iostream>
#include <string>
#include <unistd.h>
#include <map>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <Utilities.hpp>
#include <Replies.hpp>

class Client;
class Server{

    private:
        size_t                  port_number;
        const std::string       password;
        size_t                  server_fd;
        // sockaddr_in             addr;
        std::vector<Client>     clients;


        // create socket
        void createSocket(void);
        void serverAddrSocket(void) const;
        void socketListen(void) const;
        void run(void);
        int findMaxFd(void) const;

    public:
        Server(size_t port_number, const std::string password);
        ~Server();

};