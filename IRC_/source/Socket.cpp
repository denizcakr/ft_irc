#include "Server.hpp"
#include "Client.hpp"
#include "Utilities.hpp"
#include "Exception.hpp"

void Server::createSocket(void){

    ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) ?//ip4,tcp -> socket create
    throw Exception("Socket is not created!") :
    std::cout << GREEN << "Socket is created." << RESET << std::endl;

    int opt = 1;
    (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) ?
    throw Exception("Socket is not optimized!") : 
    std::cout << GREEN << "Socket is optimized." << RESET << std::endl;
}

void Server::serverAddrSocket(void) const{
    struct sockaddr_in server_addr_socket;
    memset(&server_addr_socket, 0, sizeof(struct sockaddr_in));
    server_addr_socket.sin_family = AF_INET;
    server_addr_socket.sin_addr.s_addr = INADDR_ANY; // localhost
    server_addr_socket.sin_port = htons(this->port_number); // port

    (bind(this->server_fd,(struct sockaddr *)&server_addr_socket, sizeof(server_addr_socket)) < 0) ?
    throw Exception("Socket is not bound!") :
    std::cout << GREEN << "Socket is bound." << RESET << std::endl;
}

void Server::socketListen(void) const{
    (listen(this->server_fd, 128) < 0) ? //kac socketi ayni anda dinleyebilirsin ->128
    throw Exception("Server socket can not hear you!") :
    std::cout << GREEN << "Server socket is listening you now." << RESET << std::endl;
}

int Server::findMaxFd() const{
    int maxFd = this->server_fd;

    for(std::vector<Client>::const_iterator it = this->clients.begin(); it != this->clients.end(); it++)
    {
        if (maxFd < (*it).cliFd)
            maxFd = (*it).cliFd;
    }
    return (maxFd);
}

/*

memset(&addr, 0, sizeof(sockaddr_in));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);//127.0.0.1 localhost
    addr.sin_family = AF_INET;
    addr.sin_port = htons(portNo);//portu veriyor

    if (bind(sockFd, (sockaddr *)&addr, sizeof(addr)) == -1)//birlestir
    {
        std::cerr << "bind err" << std::endl;
        close(sockFd);
        exit(1);
    }


    if (listen(sockFd, 1024) == -1)//server socket ready to listen
    {
        std::cerr << "listen err" << std::endl;
        close(sockFd);
        exit(1);
    }
*/