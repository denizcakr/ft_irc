#include "Client.hpp"
#include "Server.hpp"
#include "Utilities.hpp"

int Server::Pass(std::string &input, Client& c)
{
    if(input != "\0")
    {
        if(c.pass == "")
        {
            if (this->password == input)
            {
                std::cout << "Password is correct!" << std::endl;
                c.pass = input;
                Utilities::writeReply(c.cliFd, "Registration is Successful!");
                return 1;
            }
            else if(this->password != input)
            {
                std::cout << "Wrong Password!" << std::endl;
                Utilities::writeReply(c.cliFd, "Error: Wrong Password!");
                FD_CLR(c.cliFd, &this->readFds);
                FD_CLR(c.cliFd, &this->writeFds);
                close(c.cliFd);
                for(std::vector<Client>::iterator iter = clients.begin(); iter != clients.end(); iter++)
                {
                    if (iter->cliFd == c.cliFd)
                    {
                        this->clients.erase(iter);
                        std::cout << RED << "CS: "<< this->clients.size() << ", A client disconnected!" << RESET << std::endl;
                        return 0;
                    }
                }
            }
        }
        if(c.pass != "")
        {
            if(this->password == input)
            {
                std::cout << "Already registered! " << c.pass << std::endl;
                Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED);
            }
            else if(this->password != input)
            {
                std::cout << "Registered Account / Wrong Password!: " << c.pass << std::endl;

            }
        }
        return 0;
    }
    Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.nick, "PASS"));
    return 0;
}