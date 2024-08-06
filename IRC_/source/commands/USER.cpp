
#include "Server.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Utilities.hpp"

/*
    USER degistirilmemeli ve ayni adda user varsa izin vermemeli!
*/
int Server::User(std::string &cmd, Client& c)
{
    if(c.hexOrNc == NC)
    {
        // password kontrolüne c yollanacak
        if(cmd.size() != 1)
            Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, cmd));
        else if(!c.user.empty())
            Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED);
        else
        {
            std::string::size_type pos = cmd.find(" ");
            if (pos != std::string::npos)
            {
                c.user = cmd.substr(0, pos);
                c.user += "\n";
            }
            else
                Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, cmd));
        }
    }
        return 0;
}