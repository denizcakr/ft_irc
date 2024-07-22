#include "Exception.hpp"
#include "Utilities.hpp"

int main(int ac, char** av){
    try
    {
        if(ac != 3){ // ./ircservc <port> <password> 
            throw Exception("Follow this instructions -> ./ircserv <port> <password>");
        }
        else if(!Utilities::checkPortNumber(av[1])){
            throw Exception("Port number must be integer");
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 1;
}