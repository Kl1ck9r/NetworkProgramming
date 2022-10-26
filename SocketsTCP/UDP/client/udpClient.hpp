#ifndef UDPCLIENT_HPP
#define UDPCLIENT_HPP

#include "/home/ruslan/TCPRelize/UDPSock/Exception.hpp"
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 12345
#define SIZE 256

class udpClient:public socket_error{
public:
    udpClient();

    udpClient(const udpClient &udp)=delete;

    udpClient & operator=(const udpClient &udp)=delete;

    udpClient(udpClient &&udp) = default;

    udpClient& operator=(udpClient &&upd) = default;

    virtual ~udpClient() noexcept {close(_fd);}

public:
    void MessageHandle();

    int SendTo(int fd,const char *_buffer,size_t buffer_len,int _flags = 0)const;

    int RecvFrom(int fd,char *_buffer,size_t buffer_len,struct sockaddr_in _from,int _flags = 0);

private:
    int _fd;

    sockaddr_in serv_addr;
    sockaddr_in clien_addr;

    socklen_t size_clien=sizeof(clien_addr);
    socklen_t size_serv=sizeof(serv_addr);

};


#endif // UDPCLIENT_HPP
