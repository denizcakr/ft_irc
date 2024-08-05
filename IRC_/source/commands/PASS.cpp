#include "Client.hpp"
#include "Server.hpp"
#include "Utilities.hpp"

int Server::Pass(std::string &input, Client& c)
{
    if(c.pass == "")
    {
        if (this->password == input)
        {
            std::cout << "Password is correct!" << std::endl;
            c.pass = input;
            // reply
            return 1;
        }
        else if(this->password != input)
        {
            // reply wrong password
            FD_CLR(c.cliFd, &this->readFds);
            FD_CLR(c.cliFd, &this->writeFds);
            close(c.cliFd);
            for(std::vector<Client>::iterator iter = clients.begin(); iter != clients.end(); iter++)
            {
                std::cout << "Wrong Password!" << std::endl;
                if (iter->cliFd == c.cliFd)
                {
                    this->clients.erase(iter);
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
            // reply(ERR_ALREADYREGISTERED, c);
            size_t msg = write(c.cliFd, "Error: ALREADY REGISTERED!", strlen("Error: ALREADY REGISTERED!"));
            (void)msg;
        }
        else if(this->password != input)
        {
            std::cout << "Registered Account / Wrong Password!: " << c.pass << std::endl;

        }
    }
    return 0;
}
