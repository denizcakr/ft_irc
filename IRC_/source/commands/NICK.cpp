#include "Server.hpp"
#include "Client.hpp"

int Server::isNickExist(std::string s) {
    for(std::vector<Client>::iterator it = this->clients.begin() ; it != this->clients.end(); ++it) {
        if(it->nick == s)
            return 1;
    }
    return 0;
}

int checkInput(std::string &nickName){
    for(std::string::iterator it = nickName.begin(); it != nickName.end(); ++it){
        if(!isalnum(*it))
            return 0;
    }
    return 1;
}

int Server::Nick(std::string &s, Client &c) {// NICK <nickname>
    if(!checkInput(s)){
        Utilities::writeReply(c.cliFd, ERR_ERRONEUSNICKNAME(c.user, c.nick));
        return 0;
    }
    if(s.size() < 1){
        Utilities::writeReply(c.cliFd, ERR_NONICKNAMEGIVEN(c.user));
        return 0;
    }
    if(!s.empty() && !isNickExist(s)){
        c.nick = s;
        c.messageBox.push_back(RPL_NICK(c.nick, c.user, c.ip, s));
        FD_SET(c.cliFd, &this->writeFds);
    }
    else{
        if (s.empty())
            Utilities::writeReply(c.cliFd, ERR_NICKNAMEEMPTY(c.nick));
        else if(isNickExist(s))
            Utilities::writeReply(c.cliFd, ERR_NICKNAMEINUSE(c.nick));
    }
    return 1;
}
