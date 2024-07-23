#pragma once
#include <iostream>
#include <string>
#include <exception>
#include "Utilities.hpp"

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
