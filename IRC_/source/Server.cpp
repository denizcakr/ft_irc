#include "Server.hpp"
#include "Client.hpp"

Server::Server(size_t port_number, char* password) : port_number(port_number), password(std::string(password)){
    std::cout << this->port_number << " " << this->password << std::endl;

    createSocket();
    serverAddrSocket();
    socketListen();
}