#include "Server.hpp"
#include "Client.hpp"

Server::Server(size_t port_number, const std::string password) : port_number(port_number), password(password){
    std::cout << this->port_number << " " << this->password << std::endl;

    createSocket();
    serverAddrSocket();
    socketListen();
    std::cout << "yarrrrrak" << std::endl;
}

Server::~Server(){
    close(this->server_fd);
}