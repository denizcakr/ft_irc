#include "Client.hpp"
#include "Server.hpp"
#include "Utilities.hpp"
/*

    connect olduktan sonra ilk girilen komut PASS olmali, 
    specially hexchat
*/

// int Server::Pass(std::string &input, Client& c)
// {
//     /* input = input.substr(0, input.length()-1);
//     std::cout << "|INPUT:|" << input << "|" << std::endl; */

//     if(input != "\0")
//     {
//         if(c.pass == "")
//         {
//             if(c.hexOrNc == HEX)
//                 input = input.substr(0, input.size() - 1);
//             if (!strcmp(this->password.c_str(), input.c_str()))
//             {
//                 c.passCheck = 1;
//                 std::cout << "Password is correct!" << std::endl;
//                 c.pass = input;
//                 Utilities::writeReply(c.cliFd, "Registration is Successful!\n");
//                 return 1;
//             }
//             else if(this->password != input)
//             {
//                 std::cout << "Wrong Password!" << std::endl;
//                 Utilities::writeReply(c.cliFd, "Error: Wrong Password!\n");
//                 FD_CLR(c.cliFd, &this->readFds);
//                 FD_CLR(c.cliFd, &this->writeFds);
//                 close(c.cliFd);
//                 for(std::vector<Client>::iterator iter = clients.begin(); iter != clients.end(); iter++)
//                 {
//                     if (iter->cliFd == c.cliFd)
//                     {
//                         this->clients.erase(iter);
//                         std::cout << RED << "CS: "<< this->clients.size() << ", A client disconnected!" << RESET << std::endl;
//                         return 0;
//                     }
//                 }
//             }
//         }
//         else
//         {
//             if(this->password == input)
//             {
//                 std::cout << "Already registered! " << c.pass << std::endl;
//                 Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED(c.cliFd));
//             }
//             else if(this->password != input)
//             {
//                 std::cout << "Registered Account / Wrong Password!: " << c.pass << std::endl;

//             }
//         }
//         return 0;
//     }
//     Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "PASS"));
//     return 0;
// }

int Server::Pass(std::string &input, Client& c){

    if(this->password == input){
        c.passCheck = 1;
        std::cout << "Password is correct!" << std::endl;
        c.pass = input;
        Utilities::writeReply(c.cliFd, "Registration is Successful!\n");
        return 1;
    }
    return 0;
}
