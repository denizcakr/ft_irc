#include "Server.hpp"
#include "Client.hpp"

int Server::Cap(std::string &cmd, Client &c)
{
    if (cmd == "LS\n")
        c.cliFd = HEX;
    else if (cmd == "NC\n")
        c.cliFd = NC;
    else
        return 0;
    return 1;
}
