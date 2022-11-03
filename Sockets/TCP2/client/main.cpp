#include <iostream>
#include <memory>
#include "tcpServer.hpp"

int main() {

  try{
      tcpServer server;

      server.Bind();

      server.Listen();

      server.Accept();

      server.Send("Hello i'm server", 30, 0);

      server.HandleMessage(server);

  } catch(::err_socket &error){
        std::cerr<<error.what()<<std::endl;
  }

  return 0;
}
