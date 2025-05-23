#include <stdio.h>

enum HTTPmethods{
    GET,
    POST,
    PUT,
    HEAD,
    PATCH,
    DELETE,
    CONNECT,
    OPTIONS,
    TRACE
};

struct HTTPrequest{
    int Method;
    char *URI;
    float HTTPversion;   
};

struct HTTPrequest http_request_constructor(char *request);