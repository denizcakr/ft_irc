#include "Server.hpp"
#include "Client.hpp"

int Server::Cap(std::string &cmd, Client &c)
{
    if (cmd == "LS\n")
        c.hexOrNc = HEX;
    else if (cmd == "NC\n")
        c.hexOrNc = NC;
    else
        return 0;
    return 1;
}
