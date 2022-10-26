#include "udpServer.hpp"

udpServer::udpServer() {
  try {
    _sd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&clien_addr, 0, sizeof(clien_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

  } catch (socket_error &error) {
    std::cerr << error.what() << std::endl;
  }
}

void udpServer::Bind() const {
  if (bind(_sd, (const struct sockaddr *)&serv_addr, addr_size) < 0) {
    throw socket_error("Failed to bind socket !");
  }

  std::cout << "Bind..." << std::endl;
}

void udpServer::MessageHandle() const {
  constexpr char *message = "Hello i am server ";

  int recv_bytes;

  int send_bytes;

  while (recv_bytes > 0) {

    char _buffer[SIZE];
    memset(_buffer, 0, SIZE);

    recv_bytes = RecvFrom(_sd, _buffer, SIZE, &clien_addr);

    if (recv_bytes < 0) {
      throw socket_error("Error recv_from socket !");
    }

    std::cout << "Message from client: "
              << std::string(_buffer, 0, recv_bytes + 1) << std::endl;

    std::cout << "Server get connect from addr :"
              << inet_ntoa(clien_addr.sin_addr)
              << "Port: " << ntohs(clien_addr.sin_port) << std::endl;

    send_bytes = SendTo(_sd, message, strlen(message));

    if (send_bytes < 0) {
      throw socket_error("Error to send_to socket ");
    }
  }
}

int udpServer::SendTo(int _fd, const char *_buffer, size_t buff_len,
                      int _options) const {
  return sendto(_fd, _buffer, buff_len, _options, (const sockaddr *)&serv_addr,
                addr_size);
}

int udpServer::RecvFrom(int _fd, char *_buffer, size_t buff_len,
                        const sockaddr_in *_form, int _options) const {

  socklen_t size_form = sizeof(*_form);

  return recvfrom(_fd, _buffer, buff_len, _options, (sockaddr *)&_form,
                  &size_form);
}
