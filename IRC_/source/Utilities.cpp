#include "Utilities.hpp"

Utilities::Utilities(){}
Utilities::~Utilities(){}

int Utilities::checkPortNumber(char* port_number){ //max port number ekle

    for(int i = 0;port_number[i];i++){
        if(!isdigit(port_number[i]))
            return 0;
    }
    return 1;
}