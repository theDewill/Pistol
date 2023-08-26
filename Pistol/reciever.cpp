
#include <iostream>
#include <string>
//#include "headers/control.h"
#include <sys/socket.h>

void Reciever_Handler () {

    struct sockaddr_in_addr;
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd<0) {
        std::cout << "Error binding socket" <<std::endl;

    }
}
