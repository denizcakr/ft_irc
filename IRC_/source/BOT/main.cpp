#include "bot.hpp"
#include <exception>

int checkPortNumber(char* port_number){ //max port number

    int pN = atoi(port_number);

    for(int i = 0;port_number[i];i++){
        if(!isdigit(port_number[i]))
            return 0;
    }

    if (pN < 0 || pN > 65535)
        return 0;
    return 1;
}

int main(int ac, char **av)
{
    try
    {
        if (ac == 2 && std::string(av[1]) == "-h")
        {
            std::cout << "Follow this instructions -> ./ircbot <port> <password>" << std::endl;
            return 0;
        }
        if (ac != 3)
        { // ./ircbot <port> <password>
            throw std::runtime_error("Follow this instructions -> ./ircbot <port> <password>");
        }
        else if (!checkPortNumber(av[1]))
        {
            throw std::runtime_error("Port number must be integer");
        }
        else
        {
            Bot Bot(atoi(av[1]), std::string(av[2]));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 1;
}