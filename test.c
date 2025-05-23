#include<stdio.h>
#include "Server.h"
#include <string.h>
#include <unistd.h>

void launch(struct Server *server){
    int addr_len = sizeof(server->address);

    while(1){    
        printf("===============WAITING FOR CONNECTION===============\n");
        
        int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&addr_len);
        if(new_socket<0){
            perror("Accept Failed. \n");
            continue;
        }

        char buffer[10000];
        read(new_socket, buffer, 10000);
        printf("%s \n", buffer);

        char response[1000];
        char *body = "<html><body><h1> la pulga </h1></body></html>";
        int body_len = strlen(body);

        sprintf(response,
            "HTTP/1.1 200 OK\r\n"
            "Date: Fri, 23 May 2025 13:33:24 IST\r\n"
            "Server: Apache/2.2.14 honestly couldnt care less man\r\n"
            "Last-Modified: some random date man idk\r\n"
            "Content-Length: %d\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "%s",
            body_len,
            body
        );

        // header and body need clear seperation for response and hence the two \r\n are needed. smh.


        int response_len = strlen(response);
        write(new_socket, response, response_len);
        //write(new_socket, body, strlen(body));
        close(new_socket);
    }
}

int main(){
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 8080, 10, launch);
    server.launch(&server);

}
