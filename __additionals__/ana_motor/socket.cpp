#include "server.hpp"

int createSocket(int portNo)
{
    int sockFd;
    sockaddr_in addr;


    sockFd = socket(AF_INET, SOCK_STREAM, 0);//ipv4, tcp* -> socket creat
    if (sockFd == -1)
    {
        std::cerr << "error" << std::endl;
        exit(1);
    }

    int opt = 1; // opsiyonel
    setsockopt(sockFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));//SO_REUSEADDR->8080(port) duzgun kapat

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

    return (sockFd);
}


int server::findMaxFd()
{
    int maxFd = this->serverFd;

    for(std::vector<client>::iterator begin = this->clients.begin(); begin != this->clients.end(); begin++)
    {
        if (maxFd < (*begin).cliFd)
            maxFd = (*begin).cliFd;
    }
    return (maxFd);
}