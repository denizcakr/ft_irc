#include "Server.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Utilities.hpp"

/*
	RFC
	->ERR_NEEDMOREPARAMS (461) ++
	->ERR_ALREADYREGISTERED  ++

*/

int Server::User(std::string &input, Client& c)
{
	if(input.find_first_of(" \t") != std::string::npos) { //any space or tab 
        Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.user, "USER"));
        return 1;
    }
	if(input.size() > USERLEN) {
        input = input.substr(0, USERLEN);
		Utilities::writeReply(c.cliFd, "Username length can be maximum 12 characters.\n");
    }
	if(!c.user.empty() && c.user == input)
		Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED(c.user));
	else if(c.user.empty() && !input.empty()){
		if (c.hexOrNc == HEX)
			input = input.substr(0, input.size() - 1);
		c.user = input;
	}
	else if(input.empty() || input.size() < 1 )
		Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.user, "USER"));
	else if(!c.user.empty() && c.user != input)
		Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED(c.user));
	return 1;
}
