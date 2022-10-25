#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

int main(void)
{
    char _buffer[256];
    int n_port(0);
    int descriptor_socket(0);

    sockaddr_in client_addr;

    descriptor_socket=socket(AF_INET,SOCK_STREAM,0);

    if(descriptor_socket<0){
        std::cerr<<"Faield connect to socket !";
            exit(1);
    }

    n_port=atoi("12345");

    memset(&client_addr,0,sizeof(client_addr));

    client_addr.sin_family=AF_INET;
    client_addr.sin_addr.s_addr=INADDR_ANY;
    client_addr.sin_port=htons(n_port);

    if(connect(descriptor_socket,(struct sockaddr*)&client_addr,sizeof(client_addr))<0){
        std::cerr<<"Failed connect to server !";
           exit(1);
    }

    while(true){

     std::cout<<"Enter message to server: ";
     memset(_buffer,0,strlen(_buffer)); // clear buff

     std::cin.getline(_buffer,256,'\n');

     int tc_read=write(descriptor_socket,_buffer,256);

     if(tc_read<0){
         std::cerr<<"Failed to write message from server !";
         exit(1);
     }


     tc_read=read(descriptor_socket,_buffer,256);
         if(tc_read<0){
          std::cerr<<"Failed to read from server !";
              exit(1);
          }
    }

    close(descriptor_socket);
    return 0;
}