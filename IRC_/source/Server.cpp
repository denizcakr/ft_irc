#include "Server.hpp"
#include "Client.hpp"

Server::Server(){}

Server::Server(size_t port_number, const std::string password) : port_number(port_number), password(password){
    std::cout << this->port_number << " " << this->password << std::endl;

    createSocket();
    serverAddrSocket();
    socketListen();
    run();
    std::cout << "yarrrrrak" << std::endl;
}

void Server::run(void){

    sockaddr_in cliAddr;
    socklen_t cliSize;
    // int cliFd = -1;
    // char clientIP[INET_ADDRSTRLEN];
    // int cliPort;
    int readed;
    Client tmp;
    Server myserver;
    cliSize = sizeof(sockaddr_in);
    int state = 0;

    FD_ZERO(&this->readFds);
    FD_ZERO(&this->writeFds);
    FD_ZERO(&this->readFdsSup);
    FD_ZERO(&this->writeFdsSup);

    FD_SET(this->server_fd, &this->readFds);

    int k = -1;
    int client_size = 0;

    while (1){
        while(state == 0){
            this->readFdsSup = this->readFds;
            this->writeFdsSup = this->writeFds;

            state = select(myserver.findMaxFd() + 2, &this->readFdsSup, &this->writeFdsSup, NULL, 0);
            std::cout << ++k << " ";
        }

        if (FD_ISSET(this->server_fd, &this->readFdsSup)){
            tmp.cliFd = accept(this->server_fd, (sockaddr *)&cliAddr, &cliSize);
            if (tmp.cliFd < 0) {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    // Non-blocking soketlerde bu hata normaldir ve bağlantı olmadığı anlamına gelir.
                    continue;
                }
                throw Exception("Accept failed!");
                continue;
            }
            fcntl(tmp.cliFd, F_SETFL, O_NONBLOCK);
            tmp.cliPort = ntohs(cliAddr.sin_port);
            std::cout << "Top G:" << inet_ntop(AF_INET, &(cliAddr.sin_addr), tmp.ipAddr, INET_ADDRSTRLEN) << std::endl;//
            this->clients.push_back(tmp);
            FD_SET(tmp.cliFd, &this->readFds);

            std::cout << GREEN << "New Client Connected!" << RESET << std::endl;
            client_size++;
            std::cout << "client size "<< client_size << std::endl;
            state = 0;
        }

        for(std::vector<Client>::iterator begin = this->clients.begin(); begin != this->clients.end() && state; ++begin){
            if(FD_ISSET((*begin).cliFd, &this->readFdsSup)){
                std::cout << k << " read" << std::endl;
                readed = read((*begin).cliFd, this->buffer, 1024);
                if(readed <= 0){
                    FD_CLR((*begin).cliFd, &this->readFds);
                    FD_CLR((*begin).cliFd, &this->writeFds);
                    close((*begin).cliFd);
                    this->clients.erase(begin);
                    std::cout << "A client disconnected!" << std::endl;
                    client_size--;
                    std::cout << "client size "<< client_size << std::endl;
                }
                else{
                    this->buffer[readed] = 0;
                    std::cout << buffer << std::endl;

                    for(std::vector<Client>::iterator it = this->clients.begin(); it != this->clients.end(); ++it){
                        if(it != begin){
                            (*it).messageBox.push_back(buffer);
                            FD_SET((*it).cliFd, &this->writeFds);
                        }
                    }
                }

                state = 0;
                break;
            }
        }

        for(std::vector<Client>::iterator it = this->clients.begin(); it != this->clients.end() && state; ++it){
            if(FD_ISSET((*it).cliFd, &this->writeFdsSup)){
                std::cout << k << " write" << std::endl;
                readed = write((*it).cliFd, (char *)(*it).messageBox[0].c_str(), (*it).messageBox[0].length());
                (*it).messageBox.erase((*it).messageBox.begin());

                if((*it).messageBox.empty())
                    FD_CLR((*it).cliFd, &this->writeFds);
                
                if(readed <= 0){
                    FD_CLR((*it).cliFd, &this->readFds);
                    FD_CLR((*it).cliFd, &this->writeFds);
                    close((*it).cliFd);
                    this->clients.erase(it);
                    std::cout << "A client disconnected!" << std::endl;
                    client_size--;
                    std::cout << "client size "<< client_size << std::endl;
                }
                state = 0;
                break;
            }
        }

    }
    
}

int Server::findMaxFd() const{
    int maxFd = this->server_fd;

    for(std::vector<Client>::const_iterator begin = this->clients.begin(); begin != this->clients.end(); begin++)
    {
        if (maxFd < (*begin).cliFd)
            maxFd = (*begin).cliFd;
    }
    return (maxFd);
}

/*
    nc 
    JOIN eymen
*/

/*
void Server::initCommands(void) {
    // commands["PASS"] = &Server::Pass;
    commands["INFO"] = &Server::Info;
    commands["PRIVMSG"] = &Server::Privmsg;
    commands["JOIN"] = &Server::Join;
    commands["NICK"] = &Server::Nick;
    // commands["USER"] = &Server::User;
    commands["CAP"] = &Server::Cap;
    commands["TOPIC"] = &Server::Topic;
    commands["INVITE"] = &Server::Invite;
    commands["NOTICE"] = &Server::Notice;
    commands["KICK"] = &Server::Kick;
    commands["PART"] = &Server::Part;
    commands["PONG"] = &Server::Pong;
    commands["QUIT"] = &Server::Quit;
    // commands["WHOIS"] = &Server::Whois;
    commands["MODE"] = &Server::Mode;
}
*/

Server::~Server(){
    close(this->server_fd);
}