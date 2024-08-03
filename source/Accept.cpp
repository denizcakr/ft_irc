#include "Server.hpp"
#include "Client.hpp"

void Server::acceptClient() {
    if (!FD_ISSET(this->server_fd, &this->readFdsSup))
        return ;
    sockaddr_in cliAddr;
    socklen_t cliSize;
    Client tmp;

    cliSize = sizeof(sockaddr_in);
    tmp.cliFd = accept(this->server_fd, (sockaddr *)&cliAddr, &cliSize);
    if (tmp.cliFd < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK)// Non-blocking soketlerde bu hata normaldir ve bağlantı olmadığı anlamına gelir.
        {
            this->state = 0;
            return ;
        }
        throw Exception("Accept failed!");
    }
    fcntl(tmp.cliFd, F_SETFL, O_NONBLOCK);
    tmp.cliPort = ntohs(cliAddr.sin_port);
    std::cout << "Top G:" << inet_ntop(AF_INET, &(cliAddr.sin_addr), tmp.ipAddr, INET_ADDRSTRLEN) << std::endl;//
    this->clients.push_back(tmp);
    FD_SET(tmp.cliFd, &this->readFds);
    std::cout << GREEN << "CS: "<< this->clients.size() << ", New Client Connected!" << RESET << std::endl;
    // write(tmp.cliFd, "Enter the password using PASS <password>\n", strlen("Enter the password using PASS <password>\n"));
    this->state = 0;
}