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

class Client;
class Server{

    private:
        size_t                  port_number;
        const std::string       password;
        size_t                  server_fd;
        // sockaddr_in             addr;
        std::vector<Client>     clients;
        char                    buffer[1024];

        fd_set readFds;
        fd_set writeFds;
        fd_set readFdsSup;
        fd_set writeFdsSup;

    private:
        // create socket
        void createSocket(void);
        void serverAddrSocket(void) const;
        void socketListen(void) const;
        void run(void);
        int findMaxFd(void) const;

    public:
        Server();
        Server(size_t port_number, const std::string password);
        ~Server();

};