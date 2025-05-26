#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "HTTPrequest.h"
#include "../data-structures/lists/queue.h"

void extract_request_line(struct HTTPrequest *request, char *request_line);
void extract_header_fields(struct HTTPrequest *request, char *header_fields);
void extract_body(struct HTTPrequest *request, char *body);


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
    
    char requested[strlen(request_string)];
    strcpy(requested, request_string);
    for(int i=0;i<strlen(requested)-1;i++){
        if(requested[i]="\n" && requested[i+1]=="\n") requested[i+1]="|";
    }

    char *request_string = strtok(requested, "\n");
    char *header_fields = strtok(NULL, "|");
    char *body = strtok(NULL, "|");

    extract_request_line(&request, request_string);
    extract_header_fields(&request, header_fields);
    extract_body(&request, body);

    return request;

}

void extract_request_line(struct HTTPrequest *request, char *request_string){
    char request[strlen(request_string)];
    strcpy(request, request_string);


    char *method = strtok(request, "\n"); //destructive action
    char *uri = strtok(NULL, " ");
    char *httpversion = strtok(NULL, "\0");

    struct Dictionary request_line_dict = dict_constructor(compare_keys);
    request_line_dict.insert(&request_line, "method", sizeof("method"), method, sizeof(method));
    request_line_dict.insert(&request_line, "uri", sizeof("uri"), uri, sizeof(uri));
    request_line_dict.insert(&request_line, "http_version", sizeof("http_version"), http_version, sizeof(http_version));

    request->request_line = request_line_dict;
    if(request->request_line.search(&request->request_line, "GET", sizeof("GET")))){
        extract_body(request, (char *)request->request_line.search(&request->request_line, "uri", sizeof("uri"));
    }
}

void extract_header_fields(struct HTTPrequest *request, char *header_fields){
    char fields[strlen(header_fields)];
    strcpy(fields, header_fields);

    struct Queue headers = queue_constructor();
    char *field = strtok(fields, "\n");
    while(field){
        headers.push(&headers, field, sizeof(char[strlen(field)]));
        field = strtok(NULL, "\n");
    }

    request->header_fields = dict_constructor(compare_keys);
    char *header = (char *)peek(&headers);
    while(header){
        char *key = strtok(header, ":");
        char *value = strtok(NULL, "\0");

        if(value){
            if(value[0]==' ') value+=1;
            request->header_fields.insert( &request->header.fields, key, sizeof(key), value, sizeof(value));
        }

        headers.pop(&headers);
        header = (char *)headers.peek(&headers);
    }

    queue_destructor(&headers);
}

void extract_body(struct HTTPrequest *request, char *body){
    char *content_type = (cjar *)request->header_fields.search(&request->header_fields, "Content-Type", sizeof("Content-Type"));

    if(content_type){
        struct Dictionary body_fields = dict_constructor(compare_keys);
        if(strcmp(content_type, "application/x-www-form-urlencoded") == 0){
            struct Queue fields = queue_constructor();
            char *field = strtok(body, "&");
            while(field) {
                fields.push(&fields, field, sizeof(char[strlen(field)]));
                field = strtok(NULL, "&");
            }

            field = fields.peek(&fields);
            while(field){
                char *key = strtok(field, "=");
                char *value = strtok(NULL, "\0");

                if(value[0]==' ') value+=1;

                body_fields.insert(&body_fields, key, sizeof(char[strlen(key)]), value, sizeof(char[strlen(value)]));
                fields.pop(&fields);
                field = fields.peek(&fields);
            }

            queue_destructor(&fields);
        }
        else body_fields.insert(&body_fields, "data", sizeof("data"), body, sizeof(char[strlen(body)]));

        request->body = body_fields
    }
}

void http_request_destructor(struct HTTPrequest *request){
    dict_destructor(&request->request_line);
    dict_destructor(&request->header_fields);
    dict_destructor(&request->body);
}