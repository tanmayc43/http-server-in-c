#include<stdio.h>
#include "Server.h"

void launch(){
    printf("===============WAITING FOR CONNECTION===============\n");
    int addr_len = sizeof(server.address);
    char buffer[10000];
    int new_socket = accept(server.socket, (struct sockaddr *)&server.address, (socklen_t *)&addr_len);
    
    read(new_socket, buffer, 10000);
    printf("%s \n", buffer);

    char *greeting = "HTTP/1.1 200 OK\n Date: Fri, 23 May 2025 13:33:24 IST \n Server: Apache/2.2.14"
}

int main(){
    Struct Server server = server_constructor(AF_INET,  0, 80, 10, SOCK_STREAM)
}