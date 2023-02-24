#include <fstream>
#include "incs/Request.hpp"
#include "incs/Response.hpp"
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include "incs/Request.hpp"
#include <fcntl.h>

#define PORT 8080

int main()
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    ft::Request request;

    std::string hello;

    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    int on = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &on, sizeof(int));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[1000] = {0};
        bzero(buffer, 1000);
        valread = read( new_socket , buffer, 1000);
        std::cout << "REQUEST \n\n" << buffer << std::endl;
        std::ofstream ofs("request");

        ofs.write((char *)buffer, sizeof(buffer));
        ofs.close();
        hello = request.requestStarter(valread);
        // std::cout << hello << std::endl;
        std::ofstream ofs2("response");
        ofs2 << hello;
        write(new_socket , const_cast<char *>(hello.c_str()), hello.size());
        close(new_socket);
    }
    return 0;
}