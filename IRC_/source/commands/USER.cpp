
#include "Server.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Utilities.hpp"

int Server::User(std::string &cmd, Client& c)
{
    if(c.hexOrNc == NC)
    {
        // password kontrolüne c yollanacak
        if(cmd.size() != 1)
            Utilities::writeMessage(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, cmd));
        else if(!c.user.empty())
            Utilities::writeMessage(c.cliFd, ERR_ALREADYREGISTRED);
        else
        {
            std::string::size_type pos = cmd.find(" ");
            if (pos != std::string::npos)
            {
                c.user = cmd.substr(0, pos);
                c.user += "\n";
            }
            else
                Utilities::writeMessage(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, cmd));
        }
    }
        return 0;
}