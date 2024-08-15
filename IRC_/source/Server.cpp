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

Client* Server::find_client(std::string &user)
{
    for(ClientIterator it = clients.begin(); it != clients.end() ; ++it)
    {
        if(it->user == user)
        {
            return &(*it);
        }
    }
    return NULL;
}

void Server::sendMessageToChannel(Client& c, std::string& message, Channel &channel)
{
    for (std::vector<Client>::iterator it = channel.channel_client.begin(); it != channel.channel_client.end(); ++it)
    {
        if ((*it).user == c.user)
            continue;
        for(std::vector<Client>::iterator it2 = clients.begin(); it2 != clients.end(); ++it2){
            if((*it).user == (*it2).user){
                (*it2).messageBox.push_back(message);
                FD_SET((*it2).cliFd, &this->writeFds);
            }
        }

    }
}

void Server::cmds_initialize(void)
{
    cmds["CAP"] = &Server::Cap;
    cmds["PASS"] = &Server::Pass;
    cmds["USER"] = &Server::User;
    cmds["NICK"] = &Server::Nick;
    cmds["PRIVMSG"] = &Server::Privmsg;
    cmds["JOIN"] = &Server::Join;
    cmds["MODE"] = &Server::Mode;
    cmds["INFO"] = &Server::Info;
    cmds["TOPIC"] = &Server::Topic;
    // cmds["INVITE"] = &Server::Invite;
    // cmds["NOTICE"] = &Server::Notice;
    // cmds["KICK"] = &Server::Kick;
    cmds["PART"] = &Server::Part;
    cmds["QUIT"] = &Server::Quit;

}

Server::~Server()
{
    close(this->server_fd);
}