#include "tcpServer.hpp"

tcpServer::tcpServer() {
  try {
    fd_descript = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(_port);

  } catch (::err_socket &error) {
    std::cerr << error.what() << std::endl;
    return;
  }
}

void tcpServer::Bind() const {
  if (bind(fd_descript, (sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    throw Socket_exception("Error to bind socket");
  }

  std::cout << "Server Bind ... " << std::endl;
}

void tcpServer::Listen(uint16_t _queue) const {
  if (listen(fd_descript, _queue) < 0) {
    throw Socket_exception("Error to listen socket");
  }

  std::cout << "Server listen ... " << std::endl;
}

void tcpServer::HandleMessage(const tcpServer &tcp) {
  char _buffer[256];

  while (true) {

    memset(_buffer, 0, 256);

    int read_bites = tcp.Receive(_buffer, 256, 0);

    if (read_bites < 0) {
      std::cerr << "Failed to receive message from client!";
      exit(1);
    }

    std::cout << "From client : " << std::string(_buffer, 0, read_bites)
              << std::endl;
  }
}

int tcpServer::Accept() {
  socklen_t size_clien = sizeof(clien_addr);
  cl_descript =
      accept(fd_descript, (struct sockaddr *)&clien_addr, &size_clien);

  if (cl_descript < 0) {
    throw Socket_exception("Failed to accept from client !");
  }

  std::cout << "Server accept ... " << std::endl;

  return cl_descript;
}

int tcpServer::Receive(void *_buffer, size_t _len, int _flag) const {
  int recv_data = recv(cl_descript, _buffer, _len, _flag);

  if (recv_data < 0) {
    throw Socket_exception("Error to receive data !");
  }

  return recv_data;
}

int tcpServer::Send(const void *_buffer, size_t _len, int _flag) const {
  int recv_send = send(cl_descript, _buffer, _len, _flag);

  if (recv_send < 0) {
    throw Socket_exception("Error to send data !");
  }

  return recv_send;
}
