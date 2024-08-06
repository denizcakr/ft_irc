#include "Server.hpp"
#include "Client.hpp"

Server::Server(){}

Server::Server(size_t port_no, const std::string passwd) : port_number(port_no), password(passwd){
    std::cout << this->port_number << " " << this->password << std::endl;

    createSocket();
    cmds_initialize();
    serverAddrSocket();
    socketListen();
    run();
    std::cout << "upsydaisy!" << std::endl;
}

void Server::run(void){

    this->state = 0;

    FD_ZERO(&this->readFds);
    FD_ZERO(&this->writeFds);
    FD_ZERO(&this->readFdsSup);
    FD_ZERO(&this->writeFdsSup);

    FD_SET(this->server_fd, &this->readFds);

    while (1)
    {
        while(this->state == 0)
        {
            this->readFdsSup = this->readFds;
            this->writeFdsSup = this->writeFds;
            state = select(this->findMaxFd() + 1, &this->readFdsSup, &this->writeFdsSup, NULL, 0);
        }
        acceptClient();
        readEvent();
        writeEvent();
    }
}

Client* Server::find_client(std::string &nick)
{
    for(std::vector<Client>::iterator iter = clients.begin(); iter != clients.end(); iter++)
    {
        if(iter->nick == nick)
        {
            return &(*iter);
        }
    }
    return NULL;
}

void Server::cmds_initialize(void)
{
    cmds["PASS"] = &Server::Pass;
    // cmds["INFO"] = &Server::Info;
    cmds["PRIVMSG"] = &Server::Privmsg;
    cmds["JOIN"] = &Server::Join;
    cmds["NICK"] = &Server::Nick;
    cmds["USER"] = &Server::User;
    cmds["CAP"] = &Server::Cap;
    // cmds["TOPIC"] = &Server::Topic;
    // cmds["INVITE"] = &Server::Invite;
    // cmds["NOTICE"] = &Server::Notice;
    // cmds["KICK"] = &Server::Kick;
    // cmds["PART"] = &Server::Part;
    // cmds["PONG"] = &Server::Pong;
    // cmds["QUIT"] = &Server::Quit;
    // // cmds["WHOIS"] = &Server::Whois;
    // cmds["MODE"] = &Server::Mode;
}

Server::~Server()
{
    close(this->server_fd);
}