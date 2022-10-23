#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    
  int port_name = {0};
  int server_descript = {0};
  int client_descript = {0};

  sockaddr_in server_addr, client_addr;
  socklen_t t_socklen;

  server_descript = socket(AF_INET, SOCK_STREAM, 0);

  if (server_descript < 0) {
    std::cerr << "Failed create socket";
    exit(1);
  }

  bzero((char *)&server_addr, sizeof(server_addr));

  port_name = atoi("12345");

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(port_name);

  if (bind(server_descript, (struct sockaddr *)&server_addr,
           sizeof(server_addr)) < 0) {
    std::cerr << "Failed to bind ";
    exit(1);
  }

  if (listen(server_descript, 5) == -1) {
    std::cerr << "Failed listen new connect ";
    exit(1);
  }

  t_socklen = sizeof(client_addr);
  client_descript =
      accept(server_descript, (struct sockaddr *)&client_addr, &t_socklen);

  if (client_descript < 0) {
    std::cerr << "Failed accept connect ";
    exit(1);
  }

  std::cout << "Connect from addr: " << inet_ntoa(client_addr.sin_addr)
            << "Port: " << ntohs(client_addr.sin_port) << std::endl;

  char _buffer[256];
  send(client_descript, "Hello, Welcome to server !", strlen(_buffer), 0);

  while (true) {

    bzero(_buffer, 256); // or may use memset

    int _bytesRecv = read(client_descript, _buffer, 256);

    if (_bytesRecv < 0) {
      std::cerr << "Failed recv message from client !";
      exit(1);
    }

    if (_buffer[0] == 'E') {
      std::cout << "The client has left the server !";
      exit(1);
    }

    std::cout << "Received " << std::string(_buffer, 0, _bytesRecv)
              << std::endl;

    send(client_descript, _buffer, _bytesRecv + 1, 0);
  }

  close(client_descript);
  close(server_descript);

  return 0;
}