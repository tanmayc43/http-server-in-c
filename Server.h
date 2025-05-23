#include <sys/socket.h>
#include <netinet.h>

struct Server{
    int domain;
    int service;
    int protocol;
    int port;
    int backlog;
    u_long interface;

    struct sockaddr_in address;

    int socket;

    void (*launch)(void);
};

struct Server server_constructor(int domain, int service, int protocol, int port, int backlog, u_long interface, void(*launch)(void));
  