#include "Server.hpp"
#include "Utilities.hpp"
#include "Exception.hpp"


void Server::createSocket(void){

    if ((this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw Exception("Socket is not created!");
    }
    else
    {
        std::cout << GREEN << "Socket is created." << RESET << std::endl;
    }

    int opt = 1;

    if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        throw Exception("Socket is not optimized!");
    }
    else
    {
        std::cout << GREEN << "Socket is optimized." << RESET << std::endl;
    }
}


void Server::serverAddrSocket(void) const{

    struct sockaddr_in server_addr_socket;
    memset(&server_addr_socket, 0, sizeof(struct sockaddr_in));
    server_addr_socket.sin_family = AF_INET;
    server_addr_socket.sin_addr.s_addr = INADDR_ANY; // localhost
    server_addr_socket.sin_port = htons(this->port_number); // port number

    if (bind(this->server_fd, (struct sockaddr *)&server_addr_socket, sizeof(server_addr_socket)) < 0)
    {
        throw Exception("Socket is not bound!");
    }
    else
    {
        std::cout << GREEN << "Socket is bound." << RESET << std::endl;
    }
}

/*
    kac socketi ayni anda dinleyebilirsin ->128
*/
void Server::socketListen(void) const{

    if (listen(this->server_fd, 128) < 0)
    {
        throw Exception("Server socket can not hear you!");
    }
    else
    {
        std::cout << GREEN << "Server socket is listening you now." << RESET << std::endl;
    }
}


