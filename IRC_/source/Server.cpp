#include "Server.hpp"
#include "Client.hpp"

Server::Server(){}

Server::Server(size_t port_number, const std::string password) : port_number(port_number), password(password){
    std::cout << this->port_number << " " << this->password << std::endl;

    createSocket();
    initCommands();
    serverAddrSocket();
    socketListen();
    run();
}

void Server::run(void){

    this->state = 0;

    FD_ZERO(&this->readFds);
    FD_ZERO(&this->writeFds);
    FD_ZERO(&this->readFdsSup);
    FD_ZERO(&this->writeFdsSup);

    FD_SET(this->server_fd, &this->readFds);

    while (1) {
        while(this->state == 0){
            this->readFdsSup = this->readFds;
            this->writeFdsSup = this->writeFds;
            state = select(this->findMaxFd() + 1, &this->readFdsSup, &this->writeFdsSup, NULL, 0);
        }
        acceptClient();
        readEvent();
        writeEvent();
    }
    
}


void Server::initCommands(void) {
    // commands["PASS"] = &Server::Pass;
    // commands["INFO"] = &Server::Info;
    // commands["PRIVMSG"] = &Server::Privmsg;
    // commands["JOIN"] = &Server::Join;
    commands["NICK"] = &Server::Nick;
    // // commands["USER"] = &Server::User;
    // commands["CAP"] = &Server::Cap;
    // commands["TOPIC"] = &Server::Topic;
    // commands["INVITE"] = &Server::Invite;
    // commands["NOTICE"] = &Server::Notice;
    // commands["KICK"] = &Server::Kick;
    // commands["PART"] = &Server::Part;
    // commands["PONG"] = &Server::Pong;
    // commands["QUIT"] = &Server::Quit;
    // // commands["WHOIS"] = &Server::Whois;
    // commands["MODE"] = &Server::Mode;
}


Server::~Server(){
    close(this->server_fd);
}