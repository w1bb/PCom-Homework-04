// Copyright Valentin-Ioan Vintila 2023.
// All rights reserved.

#ifndef _WI_HELPERS_CPP_
#define _WI_HELPERS_CPP_

#include <iostream> // TODO - remove
#include <string>

using std::string;
using std::cout;
using std::endl;

#define BUFLEN 4096
#define LINELEN 1000

// - - - - -

// shows the current error
void error(const char *msg);

// adds a line to a string message
void compute_message(char *message, const char *line);

// opens a connection with server host_ip on port portno, returns a socket
int open_connection(char *host_ip, int portno, int ip_type, int socket_type, int flag);

// closes a server connection on socket sockfd
void close_connection(int sockfd);

// send a message to a server
void send_to_server(int sockfd, char *message);
void send_to_server(int sockfd, string& message);

// receives and returns the message from a server
string receive_from_server(int sockfd);

// extracts and returns a JSON from a server response
char *basic_extract_json_response(char *str);

#endif // _WI_HELPERS_CPP_
