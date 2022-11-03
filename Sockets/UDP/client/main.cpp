#include <iostream>
#include "udpClient.hpp"


int main()
{
    try{

    udpClient client;

    client.MessageHandle();

    }catch(socket_error &_error){

        std::cerr<<_error.what()<<std::endl;
    }

    return 0;
}
