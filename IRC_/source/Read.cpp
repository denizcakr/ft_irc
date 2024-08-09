#include "Server.hpp"
#include "Client.hpp"

void Server::readEvent() {
    for(std::vector<Client>::iterator begin = this->clients.begin(); begin != this->clients.end() && this->state; ++begin){
        if(FD_ISSET((*begin).cliFd, &this->readFdsSup)){
            int readed = read((*begin).cliFd, this->buffer, 1024);
            if(readed <= 0) {
                FD_CLR((*begin).cliFd, &this->readFds);
                FD_CLR((*begin).cliFd, &this->writeFds);
                close((*begin).cliFd);
                this->clients.erase(begin);
                std::cout << RED << "CS: "<< this->clients.size() << ", A client disconnected!" << RESET << std::endl;
            }
            else {
                this->buffer[readed] = '\0';
                // std::cout << "buffer |" << buffer << "|" << std::endl;//sekilli sukullu
                std::vector<std::string> lines = Utilities::splitStringByNewline(buffer);
                for(size_t i = 0; i < lines.size(); i++){
                    std::cout << "line: " << lines[i] << "|" << std::endl;
                    std::vector<std::string> all = Utilities::splitFromFirstSpace(lines[i]);
                    //std::cout << "|" << all[1] << "|" << std::endl;
                    if (cmds.find(all[0]) != cmds.end())
                    {
                        ((this->*cmds[all[0]])(all[1], (*begin)));
                    }
                    else{
                        std::cout << "Command Not Found!" << std::endl;
                    }
                }
                // for(std::vector<Client>::iterator it = this->clients.begin(); it != this->clients.end(); ++it){
                //     if(it != begin){
                //         (*it).messageBox.push_back(buffer);
                //         FD_SET((*it).cliFd, &this->writeFds);
                //     }
                // }
            }

            this->state = 0;
            break;
        }
    }
}
