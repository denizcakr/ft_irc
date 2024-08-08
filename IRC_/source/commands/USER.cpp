#include "Server.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Utilities.hpp"

/*
    USER degistirilmemeli ve ayni adda user varsa izin vermemeli!
*/
int Server::User(std::string &input, Client& c)
{
    // password kontrolüne c yollanacak
    if(!c.user.empty() && c.user == input)
        Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED);
    else if(c.user.empty() && !input.empty())
        c.user = input;
    else if(input.empty())
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.user, "USER"));
    else if(!c.user.empty() && c.user != input)
        Utilities::writeReply(c.cliFd, ERR_BADINPUTUSER);
    return 1;
}
// inputun sonunda \r varmi