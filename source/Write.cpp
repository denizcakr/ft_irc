#include "Server.hpp"
#include "Client.hpp"

void Server::writeEvent() {
    for(std::vector<Client>::iterator it = this->clients.begin(); it != this->clients.end() && state; ++it){
        if(FD_ISSET((*it).cliFd, &this->writeFdsSup)){
            int readed = write((*it).cliFd, (char *)(*it).messageBox[0].c_str(), (*it).messageBox[0].length());
            (*it).messageBox.erase((*it).messageBox.begin());

            if((*it).messageBox.empty())
                FD_CLR((*it).cliFd, &this->writeFds);
            
            if(readed <= 0){
                FD_CLR((*it).cliFd, &this->readFds);
                FD_CLR((*it).cliFd, &this->writeFds);
                close((*it).cliFd);
                this->clients.erase(it);
                std::cout << RED << "CS: "<< this->clients.size() << ", A client disconnected!" << RESET << std::endl;
            }
            state = 0;
            break;
        }
    }
}