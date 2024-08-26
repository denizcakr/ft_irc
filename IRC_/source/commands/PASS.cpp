#include "Client.hpp"
#include "Server.hpp"
#include "Utilities.hpp"


int Server::Pass(std::string &input, Client& c){

    // std::cout << "input " << input << std::endl;
    if(input.empty()){
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "PASS"));
        return 0;
    }
    if(this->password == input){
        if(!c.pass.empty()){
            Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED(c.user));
        }
        else{
            c.passCheck = 1;
            std::cout << "Password is correct!" << std::endl;
            c.pass = input;
            Utilities::writeReply(c.cliFd, "Registration is Successful!\n");
            return 1;
        }
    }
    else{
        Utilities::writeReply(c.cliFd, ERR_PASSWDMISMATCH(c.user));
    }
    return 0;
}
