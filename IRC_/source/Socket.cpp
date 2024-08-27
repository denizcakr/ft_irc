#include "Server.hpp"
#include "Utilities.hpp"
#include "Exception.hpp"

void Server::createSocket(void)
{
    this->server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if ((int)(this->server_fd) < 0)
    {
        throw std::runtime_error("Socket is not created!");

    }
    else
    {
        std::cout << GREEN << "Socket is created." << RESET << std::endl;
    }

    if (fcntl(this->server_fd, F_SETFL, O_NONBLOCK) < 0) {
        close(this->server_fd);
        throw std::runtime_error("Failed to set socket to non-blocking mode");
    }
    int opt = 1;

    if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        throw std::runtime_error("Socket is not optimized!");

    }
    else
    {
        std::cout << GREEN << "Socket is optimized." << RESET << std::endl;
    }
}

void Server::serverAddrSocket(void) {

    memset(&this->addr, 0, sizeof(sockaddr_in));
    this->addr.sin_addr.s_addr = htonl(INADDR_ANY); // localhost
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(this->port_number); // port number

    if (bind(this->server_fd, (sockaddr *)&this->addr, sizeof(this->addr)) < 0)
    {
        throw std::runtime_error("Socket is not bound!");

    }
    else
    {
        std::cout << GREEN << "Socket is bound." << RESET << std::endl;
    }
}

/*
    how many sockets can you listen at the same time ->128
*/
void Server::socketListen(void) const{

    if (listen(this->server_fd, 128) < 0)
    {
        throw std::runtime_error("Server socket cannot hear you!");

    }
    else
    {
        std::cout << GREEN << "Server socket is listening you now." << RESET << std::endl;
    }
}


