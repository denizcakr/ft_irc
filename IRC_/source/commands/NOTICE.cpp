#include "Server.hpp"

int Server::isClientInChannel(Client &c, std::string channelName){
    int ret = 1;
    for(ChannelIterator it = this->channels.begin(); it != this->channels.end(); ++it, ++ret){
        if((*it).channel_name == channelName){
            for(ClientIterator cliIt = (*it).channel_client.begin(); cliIt != (*it).channel_client.end(); ++cliIt){
                if((*cliIt).cliFd == c.cliFd)
                    return ret;
            }
            break;
        }
    }
    return 0;
}

int Server::Notice(std::string &arg, Client& c){
    /*
        NOTICE #a hello
        NOTICE eyms hello
    */
    std::vector<std::string> param = Utilities::parseCmd(arg);

    // if(param[1][0] == ':'){
    //     param[1][0] = param[1].substr(1, param[1].length());
    // }
    for(ClientIterator it = clients.begin(); it != clients.end(); ++it){
        if((*it).nick == param[0] || (*it).user == param[0]){ // param[0] -> eyms
            (*it).messageBox.push_back(RPL_NOTICE(c.getPrefix(), param[0], (param[1][0] == ':' ? param[1].substr(1, param[1].length()) : param[1])));
            FD_SET((*it).cliFd, &this->writeFds);
        }
        else if(isClientInChannel((*it), param[0]) && c.nick != it->nick) {
            (*it).messageBox.push_back(RPL_NOTICE(c.getPrefix(), param[0], (param[1][0] == ':' ? param[1].substr(1, param[1].length()) : param[1])));
            FD_SET((*it).cliFd, &this->writeFds);
        }
    }
    return 0;

}