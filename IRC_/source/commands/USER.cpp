#include "Server.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Utilities.hpp"

/*
    USER degistirilmemeli ve ayni adda user varsa izin vermemeli!
*/
int Server::User(std::string &input, Client& c)
{
    std::string tmp = Utilities::splitFromFirstSpace(input)[0];
    // password kontrolüne c yollanacak
    if(!c.user.empty() && c.user == input)
        Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED);
    else if(c.user.empty() && !input.empty())
        c.user = tmp;
    else if(input.empty())
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.user, "USER"));
    else if(!c.user.empty() && c.user != input)
        Utilities::writeReply(c.cliFd, ERR_BADINPUTUSER);
    return 1;
}
// inputun sonunda \r varmi