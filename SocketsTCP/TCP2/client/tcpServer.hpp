#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include "exception.hpp"
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

class tcpServer:public Socket_exception{
public:
    tcpServer();

    tcpServer(const tcpServer &tcp) = delete;

    tcpServer & operator =(const tcpServer &tcp) = delete;

    tcpServer(tcpServer &&tcp) = default;

    tcpServer & operator=(tcpServer &&tcp) = default;

    virtual  ~tcpServer() noexcept {  close(cl_descript);close(fd_descript);   }

public:
    void HandleMessage(const tcpServer &tcp);

   void Bind() const ;

   void  Listen(uint16_t _queue = 5 )const;

   int Send(const void *_buffer,size_t _len,int _flag=0) const;

   int  Receive(void *_buffer,size_t _len,int _flag=0)const;

   int Accept();

private:
    struct sockaddr_in serv_addr;

    struct sockaddr_in clien_addr;

    int fd_descript;
    int cl_descript;
    int _port =  12345 ;
};


#endif // TCPSERVER_HPP
