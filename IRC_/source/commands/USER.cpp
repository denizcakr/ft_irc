#include "Server.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Utilities.hpp"

int Server::User(std::string &input, Client& c)
{
    if(!c.user.empty() && c.user == input)
        Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED);
    else if(c.user.empty() && !input.empty()){
        if (c.hexOrNc == HEX)
            input = input.substr(0, input.size() - 1);
        c.user = input;
    }
    else if(input.empty())
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.user, "USER"));
    else if(!c.user.empty() && c.user != input)
        Utilities::writeReply(c.cliFd, ERR_BADINPUTUSER);
    return 1;
}
