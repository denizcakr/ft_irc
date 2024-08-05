#include "Server.hpp"
#include "Client.hpp"

int Server::Cap(std::string &input, Client &c)
{
    if (input == "LS\n")
        c.hexOrNc = HEX;
    else if (input == "NC\n")
        c.hexOrNc = NC;
    else
        return 0;
    return 1;
}
