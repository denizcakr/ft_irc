#pragma once
#include <iostream>
#include <string>
#include "Server.hpp"
#include <stdlib.h>

# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define PURPLE		"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"
# define END		"\033[m"
# define RESET		"\033[0m"



# define BUG 1


class Utilities{

    private:
        Utilities();
        ~Utilities();

    public:
        static void writeReply(int fd, std::string message);
        static void writeAllClient(std::vector<int> fd, std::string message);
        static int checkPortNumber(char* port_number);
        static std::vector<std::string> splitFromFirstSpace(const std::string& input);


};