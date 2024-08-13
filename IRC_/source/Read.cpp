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
                std::cout << RED << "CS: "<< this->clients.size() << ", " << (*begin).nick << " client disconnected!" <<RESET << std::endl;
            }
            else {
                this->buffer[readed] = '\0';
                std::string k = this->buffer;
                // if (k == "\n") {
                //     state = 0;
                //     break;
                // }
                // // ^D
                // if (k[k.length() - 1] != '\n') {
                //     (*begin).buffer += k;
                //     state = 0;
                //     break;
                // }
                std::vector<std::string> lines = Utilities::splitStringByNewline(buffer);
                for(size_t i = 0; i < lines.size(); i++){
                    std::cout << BLUE << "[ CMD ] "<<  RESET << PURPLE << "[ "<< lines[i].substr(0, lines[i].size() - 1) << " ]" << RESET << std::endl; 
                    std::vector<std::string> all = Utilities::splitFromFirstSpace(lines[i]);
                    if (cmds.find(all[0]) != cmds.end())
                    {
                        ((this->*cmds[all[0]])(all[1], (*begin)));
                    }
                    else{
                        std::cout << "Command Not Found!" << std::endl;
                    }
                }
                if(!(Utilities::parseCmd(lines[0])[0] == "CAP" && lines.size() == 1)){
                    if (!(*begin).passCheck) {
                        FD_CLR((*begin).cliFd, &this->readFds);
                        FD_CLR((*begin).cliFd, &this->writeFds);
                        std::cout << RED << (*begin).cliFd - 3 << " YOU MUST ENTER THE PASSWORD!" << RESET << std::endl;
                        std::cout << RED << "CS: "<< this->clients.size() << ", " << " client disconnected!" <<RESET << std::endl;
                        close((*begin).cliFd);//sikintili
                        this->clients.erase(begin);//sikintili
                    }
                }
            }

            this->state = 0;
            break;
        }
    }
}
