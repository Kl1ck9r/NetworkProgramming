
#include "udpClient.hpp"

udpClient::udpClient() {
  try {
    _fd = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

  } catch (socket_error &error) {
    std::cerr << error.what() << std::endl;
  }
}

void udpClient::MessageHandle() {
  const char *message = "Hello i am client !";
  int send_bytes;

  int recv_bytes;

  do{

    char _buffer[SIZE];

    std::cout << "Enter message to server: ";
    memset(_buffer, 0, SIZE);

    std::cin.getline(_buffer, SIZE, '\n');

    send_bytes = SendTo(_fd, message, strlen(message));

    if (send_bytes < 0) {
      throw socket_error("Error on send message !");
    }

    memset(_buffer, 0, SIZE);

    recv_bytes = RecvFrom(_fd, _buffer, SIZE, clien_addr);

    if (recv_bytes < 0) {
      throw socket_error("Error receive message !");
    }

    std::cout << "From Server: " << std::string(_buffer, 0, recv_bytes);
  }while(recv_bytes>0);
}

int udpClient::SendTo(int fd, const char *_buffer, size_t buffer_len,
                      int _flags) const {
  return sendto(fd, _buffer, buffer_len, _flags, (sockaddr *)&serv_addr,
                size_serv);
}

int udpClient::RecvFrom(int fd, char *_buffer, size_t buffer_len,
                        sockaddr_in _from, int _flags) {
  return recvfrom(fd, _buffer, buffer_len, _flags, (sockaddr *)&_from,
                  &size_clien);
}

