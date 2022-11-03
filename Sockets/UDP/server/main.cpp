#include <iostream>
#include "udpServer.hpp"


int main()
{
    try{
      udpServer server;

      server.Bind();
      server.MessageHandle();

    }
    catch(socket_error &_error){
        std::cerr<<_error.what()<<std::endl;
    }

    return 0;
}
