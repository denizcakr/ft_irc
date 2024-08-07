#include "Server.hpp"
#include "Client.hpp"

int Server::Cap(std::string &input, Client &c)
{
    if (input == "LS\r")
        c.hexOrNc = HEX;
    else
        c.hexOrNc = NC;
    return 1;
}
