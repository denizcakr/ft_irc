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



void Utilities::writeReply(int fd, std::string message){
    if (write(fd, message.c_str(), message.length()) < 0){
        std::cout << "Message cannot be sent!" << std::endl;
    }
}

void Utilities::writeAllMessage(std::vector<int> const& fd, std::string const& message)
{
    for (std::vector<int>::const_iterator it = fd.begin(); it != fd.end(); ++it) {
        Utilities::writeReply((*it), message);
    }
}

void Utilities::writeAllClient(std::vector<int> fd, std::string message){
    for(std::vector<int>::iterator it = fd.begin(); it != fd.end(); ++it){
        Utilities::writeReply((*it), message);
    }
}

std::vector<std::string> Utilities::splitStringByNewline(const std::string& str) {
    std::vector<std::string> result;
    std::string::size_type start = 0;
    std::string::size_type end = str.find('\n');

    while (end != std::string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find('\n', start);
    }

    // Add the last segment
    // result.push_back(str.substr(start));

    return result;
}

void Server::showRightGui(Client &client, Channel &channel) {
    std::string msg;
    Channel* tmp = getChannel(channel.channel_name);

    if (!tmp)
        return;
    // Kullanıcıların listesini oluştur
    for (std::vector<Client>::iterator it = tmp->channel_client.begin(); it != tmp->channel_client.end(); ++it) {
        msg += it->nick + " ";
    }

    // Eğer msg boşsa, kullanıcı listesinin doğru oluşturulmadığını anlayabiliriz
    // if (msg.empty()) {
    //     std::cout << "List is empty!" << std::endl;
    //     return;
    // }
    // Kullanıcıya kanalın kullanıcılarını gönder

    Utilities::writeAllClient(tmp->getFds(), RPL_NAMREPLY(client.nick, tmp->channel_name, msg));
    Utilities::writeAllClient(tmp->getFds(), RPL_ENDOFNAMES(client.nick, tmp->channel_name));
}
