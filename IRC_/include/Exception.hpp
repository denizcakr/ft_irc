#pragma once
#include <iostream>
#include <string>
#include <exception>
#include "Utilities.hpp"

# define RESET		"\033[0m"
# define RED		"\033[0;31m"



class Exception : public std::exception {
    private:
        const char* _msg_;

    public:
        Exception(const char* msg) : _msg_(msg) {}

        virtual const char* what() const throw(){
            static std::string msg = std::string(RED) + "Error: " + this->_msg_ + RESET;
            return(msg.c_str());
        }
};
