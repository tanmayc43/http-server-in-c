#include "Server.h"
#include <stdio.h>
#include <stdlib.h>


struct Server sever_constructor(int domain, int protocol, int port, int backlog, int service, u_long interface, void(*launch)(void)){
    Struct Server server;

    server.domain = domain;
    server.protocol = protocol;
    server.port = port;
    server.service = service;
    server.interface = interface;
    server.backlog = backlog;
    
    server.address.sin_family =  domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_ddr = htonl(interface);
    
    server.socket = socket(domain, service, protocol)

    if(server.socket == 0){
        perror("Failed to connect to socket. \n");
        exit(1);  
    }

    if(bind(server.socket, (struct sockaddr * )&server.address, sizeof(server.address)) < 0 ){
        perror("Binding of Server and Socket failed. \n");
        exit(1);
    }
    else{
        printf("Server and Socket bound. \n");
    }

    if(listen(server.socket, server.backlog) < 0){
        perror("Failed to listen. \n");
        exit(1);
    }
    else{
        printf("Server listening ... \n");
    }

    server.launch = launch;

    return server;
}

