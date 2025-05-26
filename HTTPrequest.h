#include <stdio.h>
#include "../data-structures/dictionary/dictionary.h"

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

    struct Dictionary request_line;
    struct Dictionary header_fields;
    struct Dictionary body;
    
};

struct HTTPrequest http_request_constructor(char *request);