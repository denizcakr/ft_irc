#include "Server.hpp"
#include "Client.hpp"
#include "Replies.hpp"
#include "Utilities.hpp"

int Server::isUserExist(std::string s) {
    for(std::vector<Client>::iterator it = this->clients.begin() ; it != this->clients.end(); ++it) {
        if(it->user == s)
            return 1;
    }
    return 0;
}

int checkOnlyTabOrSpaces(std::string &input) {
	int a = 0;
	for (int i = 0; input[i]; i++) {
		if (input[i] == ' ' || input[i] == '\t')
			a++;
	}
	return a == (int)input.size();
}

int Server::User(std::string &input, Client& c)
{

	if(isUserExist(input)){
		Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED(c.user));
		return 0;
	}

	if(input.size() > USERLEN) {
		input = input.substr(0, USERLEN);
		Utilities::writeReply(c.cliFd, "Username length can be maximum 12 characters.\n");
	}
	if(checkOnlyTabOrSpaces(input)){
		Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.user, "USER"));
		return 0;
	}
	if(!c.user.empty() && c.user == input)
		Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED(c.user));
	else if(c.user.empty() && !input.empty()){
		c.user = Utilities::splitFromFirstSpace(input)[0];

	}
	else if(input.empty() || input.size() < 1 )
		Utilities::writeReply(c.cliFd, ERR_NEEDMOREPARAMS(c.user, "USER"));
	else if(!c.user.empty() && c.user != input)
		Utilities::writeReply(c.cliFd, ERR_ALREADYREGISTRED(c.user));
	return 1;
}
