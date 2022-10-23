#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdlib>
#include <sys/time.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>



int main(void)
{
    int port_name = {0};
    int server_descript = {0};
    int client_descript = {0};

    sockaddr_in server_addr,client_addr;
    socklen_t t_socklen;

    server_descript=socket(AF_INET,SOCK_STREAM,0);

    if(server_descript<0){
        std::cerr<<"Failed create socket";
         exit(1);
    }

    bzero((char *) &server_addr, sizeof(server_addr));

    port_name=atoi("12345");

    server_addr.sin_family=AF_INET;
    server_addr.sin_addr.s_addr=INADDR_ANY;
    server_addr.sin_port=htons(port_name);

    if(bind(server_descript,(struct sockaddr *)&server_addr,sizeof(server_addr))<0){
         std::cerr<<"Failed to bind ";
            exit(1);
    }

    if(listen(server_descript,5)==-1){
        std::cerr<<"Failed listen new connect ";
          exit(1);
    }

    t_socklen=sizeof(client_addr);
    client_descript=accept(server_descript,(struct sockaddr*)&client_addr,&t_socklen);

    if(client_descript<0){
        std::cerr<<"Failed accept connect ";
            exit(1);
    }

    std::cout<<"Connect from addr: "<<inet_ntoa(client_addr.sin_addr)
             <<"Port: "<<ntohs(client_addr.sin_port)<<std::endl;

    char _buffer[256];
    send(client_descript,"Hello, Welcome to server !",strlen(_buffer),0);

    int _num=read(client_descript,_buffer,strlen(_buffer));

    if(_num<0){
        std::cerr<<"Failed to read of socket";
            exit(1);
    }

    std::cout<<"Message from client: "<<_buffer<<std::endl;

    close(client_descript);
    close(server_descript);

    return 0;
}



/*
int main(void)
{
    int number_port(0);
    int sock_tcp(0),othersock_tcp;

    struct sockaddr_in serv_addr,clien_addr;
    socklen_t t_clien;
    char buffer[256];

    sock_tcp=socket(AF_INET,SOCK_STREAM,0);

    if(sock_tcp==-1){
        std::cerr<<"Failed open conenct socket";
          exit(1);
    }

    bzero((char*)&serv_addr,sizeof(serv_addr));

    number_port=atoi("12345");

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY; // get any addres
    serv_addr.sin_port=htons(number_port);


    if(bind(sock_tcp,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
        std::cerr<<"Failed bind socket";
        exit(1);
    }

    listen(sock_tcp,5);
    t_clien=sizeof(clien_addr);

    othersock_tcp=accept(sock_tcp,(struct sockaddr*)&clien_addr,&t_clien);

    if(othersock_tcp==-1){
        std::cerr<<"Failed accept to connect";
         exit(1);
    }

    std::cout<<"Connect from"<<inet_ntoa(clien_addr.sin_addr)<<
               " And port : "<<htons(clien_addr.sin_port)<<std::endl;


    send(othersock_tcp,"Hello i'm server !",50,0);

    bzero(buffer,256);

    int n_read=read(othersock_tcp,buffer,256);

    if(n_read<0){
        std::cerr<<"Failed to read from othersock";
         exit(1);
    }

    std::cout<<"Message from othersock: "<<buffer<<std::endl;

    close(othersock_tcp);
    close(sock_tcp);

    return 0;
}
*/
