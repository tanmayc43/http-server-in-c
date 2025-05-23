#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HTTPrequest.h"


int method_selector(char *method){
    if(strcmp(method, "GET")==0) return
    else if(strcmp(method, "POST")==0) return POST;
    else if(strcmp(method, "PUT")==0) return PUT;
    else if(strcmp(method, "HEAD")==0) return HEAD;
    else if(strcmp(method, "PATCH")==0) return PATCH;
    else if(strcmp(method, "DELETE")==0) return DELETE;
    else if(strcmp(method, "CONNECT")==0) return CONNECT;
    else if(strcmp(method, "OPTIONS")==0) return OPTIONS;
    else if(strcmp(method, "TRACE")==0) return TRACE;
}

struct HTTPrequest http_request_constructor(char *request_string){

//going to use delimiter to chop up the request string for relevant details
    struct HTTPrequest request;
    //given request_string is immutable (literal)
    char request[strlen(request_string)];
    strcpy(request, request_string);

    for(int i=0;i<strlen(request)-1;i++){
        if(request[i]=='\n' && request[i+1]=='\n') request[i+1]='|';
    }

    char *request_line = strtok(request, "\n"); //destructive action
    char *headers = strtok(NULL, "|");
    char *body = strtok(NULL, "|");

    char *method = strtok(request_line, " ");
    request.Method = method_selector(method);

    char *uri = strtok(NULL, " ");
    request.URI = uri;

    char *httpversion = strtok(NULL, " ");
    httpversion = strtok(httpversion, "/");
    httpversion = strtok(NULL, "/");

    request.HTTPversion =  (float)atof(httpversion);
    
    return request;
}