#include "Exception.hpp"
#include "Utilities.hpp"
#include "Server.hpp"
#include <iostream>

int main(int ac, char** av){
    try
    {
        if (ac == 2 && std::string(av[1]) == "-h"){
            std::cout << "Follow this instructions -> ./ircserv <port> <password>" << std::endl;
            return 0;
        }
        if(ac != 3){ // ./ircservc <port> <password> 
            throw Exception("Follow this instructions -> ./ircserv <port> <password>");
        }
        else if(!Utilities::checkPortNumber(av[1])){
            throw Exception("Port number must be integer");
        }
        else {
            Server server(atoi(av[1]), std::string(av[2]));
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 1;
}