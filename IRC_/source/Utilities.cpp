#include "Utilities.hpp"

Utilities::Utilities(){}
Utilities::~Utilities(){}

int Utilities::checkPortNumber(char* port_number){ //max port number ekle

    int pN = std::atoi(port_number);

    for(int i = 0;port_number[i];i++){
        if(!isdigit(port_number[i]))
            return 0;
    }

    if (pN < 0 || pN > 65535)
        return 0;
    return 1;
}