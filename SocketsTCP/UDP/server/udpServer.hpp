#ifndef UDPSERVER_H
#define UDPSERVER_H

#include "Exception.hpp"
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 12345
#define SIZE 256

class udpServer:public socket_error{
public:
    udpServer();

    udpServer(const udpServer &udp) = delete;

    udpServer & operator=(const udpServer &udp) = delete;

    udpServer &operator=(udpServer &&udp) = default;

    udpServer(udpServer &&udp) = default;

   virtual ~udpServer() noexcept  { close(_sd); }

public:
    void Bind()const;

    void MessageHandle()const;

    int SendTo(int _fd,const char *_buffer,size_t buff_len,int _options = 0)const;

    int RecvFrom(int _fd,char *_buffer,size_t buff_len,const sockaddr_in *_from,int _options = 0)const;

private:
    int _sd;

    sockaddr_in serv_addr;

    sockaddr_in clien_addr;

    size_t addr_size=sizeof(serv_addr);
};


#endif // UDPSERVER_H
