#include "Utilities.hpp"
#include "Server.hpp"
#include "Client.hpp"

Utilities::Utilities(){}
Utilities::~Utilities(){}

int Utilities::checkPortNumber(char* port_number){ //max port number

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

std::vector<std::string> Utilities::splitString(const std::string& input, char delimiter) {
    std::vector<std::string> result;
    std::string::size_type start = 0;
    std::string::size_type end = input.find(delimiter);

    while (end != std::string::npos) {
        if (end != start) {
            result.push_back(input.substr(start, end - start));
        }
        start = end + 1;
        end = input.find(delimiter, start);
    }

    if (start < input.length()) {
        result.push_back(input.substr(start));
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
    return result;
}

void Server::showRightGui(Client &client, Channel &channel) {
    
    if (!channel.is_member(client)) {
        std::cerr << "Error: Client is not a member of the channel." << std::endl;
        return;
    }
    if(client.cliFd < 0 || channel.channel_client.empty())
        return;

    std::string msg;
    Channel* tmp = getChannel(channel.channel_name);


    if (!tmp)
        return;
    for (std::vector<Client>::iterator it = tmp->channel_client.begin(); it != tmp->channel_client.end(); ++it) {
        if(it == tmp->channel_client.begin())
            msg += "@" + it->nick + " ";
        else
            msg += ' ' + it->nick + " ";
    }    
    Utilities::writeAllClient(tmp->getFds(), RPL_NAMREPLY(client.nick, tmp->channel_name, msg));
    Utilities::writeAllClient(tmp->getFds(), RPL_ENDOFNAMES(client.nick, tmp->channel_name));

}

void Server::showRightGuiButBetter(Client &client, Channel &channel) {
    

    if(client.cliFd < 0 || channel.channel_client.empty())
        return;

    std::string msg;
    Channel* tmp = getChannel(channel.channel_name);


    if (!tmp)
        return;
    for (std::vector<Client>::iterator it = tmp->channel_client.begin(); it != tmp->channel_client.end(); ++it) {
        if(it == tmp->channel_client.begin())
            msg += "@" + it->nick + " ";
        else
            msg += ' ' + it->nick + " ";
    }    
    Utilities::writeAllClient(tmp->getFds(), RPL_NAMREPLY(client.nick, tmp->channel_name, msg));
    Utilities::writeAllClient(tmp->getFds(), RPL_ENDOFNAMES(client.nick, tmp->channel_name));

}

std::vector<std::string> Utilities::parseCmd(std::string& cmd){

    std::vector<std::string> result;
    std::string::size_type start = 0;
    std::string::size_type end = 0;

    while (end != std::string::npos) {
        end = cmd.find(' ', start);

        // Add the word to the result vector
        if (end != std::string::npos) {
            result.push_back(cmd.substr(start, end - start));
            start = end + 1;
        } else {
            // Add the last word
            result.push_back(cmd.substr(start));
        }
    }
    return result;
}

void Server::kickClient(ClientIterator& it)
{
    std::cout << RED << "Client " << it->cliFd - 3  << " disconnected!" << RESET << std::endl;
    FD_CLR(it->cliFd, &readFds);
    FD_CLR(it->cliFd, &writeFds);
    close(it->cliFd);
    clients.erase(it);
}

int Server::isChannelExist(std::string const& channelName)
{
    for (ChannelIterator it = channels.begin(); it != channels.end(); ++it) {
        if (it->channel_name == channelName)
            return 1;
    }
    return 0;
}

bool Utilities::checkChannel(std::string& s) {
    if(s.size() < 2 || s.size() > 50)
        return false;
    for(int i = 0; s[i]; i++) {
        if(s[i] == ' ' || s[i] == 7 || s[i] == ',')
            return false;
    }
    return true;
}

void Utilities::printChannelMembers(Channel& channel)
{
	std::cout << YELLOW << "< CHANNEL INFO >" << RESET << std::endl;
	for(std::vector<Client>::const_iterator it = channel.channel_client.begin(); it != channel.channel_client.end(); ++it) {
		const Client& client = *it;
		std::cout << CYAN << "Channel :  " << channel.channel_name << std::endl;
		std::cout << "User : " << client.user << std::endl;
		std::cout << "Nickname : " << client.nick << RESET <<std::endl;
        std::cout << std::endl;
        std::cout << YELLOW << "OPERATOR : " << channel.channel_client[0].user << RESET << std::endl;
	}
}

std::string Utilities::infoMessage(void){
    std::string msg;

    msg += "* 42 Ecole IRC Project \n";
    msg += "* Developers: \n";
    msg += "* - Eymen Hafsa Albayrak \n";
    msg += "* - Ezgi Deniz Çakır \n";
    msg += "* - Sümeyra Yıldız \n";
    msg += "* \n";
    msg += "* Project Information: \n";
    msg += "* - Start Date: 16/07/2024 \n";
    msg += "* - End Date: ../08/2024 \n";
    msg += "* Thanks to the following individuals for their contributions: \n";
    msg += "* - ayalman         Alp Arda Yalman \n";
    msg += "* - tacikgoz        Talha Açıkgöz \n";
    msg += "* \n";
    msg += "* End of /INFO list. \n";

    return msg;
}