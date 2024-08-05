#include "Utilities.hpp"
#include "Server.hpp"
#include "Client.hpp"

Utilities::Utilities(){}
Utilities::~Utilities(){}

int Utilities::checkPortNumber(char* port_number){ //max port number ekle

    int pN = atoi(port_number);

    for(int i = 0;port_number[i];i++){
        if(!isdigit(port_number[i]))
            return 0;
    }

    if (pN < 0 || pN > 65535)
        return 0;
    return 1;
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

std::vector<std::string> Utilities::splitFromFirstSpace(const std::string& input) {
    std::vector<std::string> result;
    size_t spacePos = input.find(' ');
    std::string temp = input;
    if (input[input.size()-1] == '\n') {
        temp = input.substr(0, input.size() - 1);
    }
    if (spacePos != std::string::npos) {
        result.push_back(temp.substr(0, spacePos));
        result.push_back(temp.substr(spacePos + 1));
    } else {
        // If no space is found, the whole string is the first part, and the second part is empty.
        result.push_back(temp);
        result.push_back("");
    }
    return result;
}

void Utilities::writeMessage(int socket, std::string const& message)
{
    if ((write(socket, message.c_str(), message.length())) < 0)
        std::cout << "Message cannot send!" << std::endl;
}
