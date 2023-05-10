#ifndef _WI_REQUESTS_
#define _WI_REQUESTS_

#include <stdlib.h>     /* exit, atoi, malloc, free */
#include <stdio.h>
#include <unistd.h>     /* read, write, close */
#include <string.h>     /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h>      /* struct hostent, gethostbyname */
#include <arpa/inet.h>
#include "helpers.h"
#include <string>
#include <vector>
#include <sstream>

using std::string;
using std::vector;
using std::stringstream;

#define HTTP_NL "\r\n"

// - - - - -

// computes and returns a GET request string (query_params
// and cookies can be set to NULL if not needed)
string compute_get_request(
    string host, string url,
    string header, string cookie
);

string compute_get_request(
    string host, string url,
    vector<string> cookies
);

// - - - - -

// computes and returns a POST request string (cookies can be NULL if not needed)
string compute_post_request(
    string host, string url, string content_type,
    vector<string> body_data, string header, string cookie
);

string compute_post_request(
    string host, string url, string content_type,
    vector<string> body_data, vector<string> cookies
);

// - - - - -

string compute_delete_request(
    string host, string url,
    string header, string cookie
);

string compute_delete_request(
    string host, string url,
    vector<string> cookies
);

#endif // _WI_REQUESTS_
