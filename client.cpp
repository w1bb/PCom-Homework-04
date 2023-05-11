// Copyright Valentin-Ioan Vintila 2023.
// All rights reserved.

#include <iostream>
#include <string>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

// Include JSON support
#include "nlohmann/json.hpp"

// Include our headers
#include "structures.hpp"
#include "requests.hpp"
#include "helpers.hpp"
#include "buffer.hpp"
#include "misc.hpp"

// - - - - -

using std::string;
using std::cout;
using std::cerr;
using std::endl;

#define IP "34.254.242.81"
#define PORT 8080

// - - - - -

string interact_register(int sockfd) {
    credentials_t new_credentials;
    new_credentials.read();

    string message = compute_post_request(
        IP, "/api/v1/tema/auth/register", "application/json",
        {new_credentials.to_json().dump()}
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error")
        throw "interact_register() -> receive_from_server() error";
    return response;
}

string interact_login(int sockfd) {
    credentials_t new_credentials;
    new_credentials.read();

    string message = compute_post_request(
        IP, "/api/v1/tema/auth/login", "application/json",
        {new_credentials.to_json().dump()}
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error")
        throw "interact_login() -> receive_from_server() error";
    return response;
}

string interact_access(int sockfd, string url, string cookie) {
    string message = compute_get_request(
        IP, url, {cookie}
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error")
        throw "interact_access() -> receive_from_server() error";
    return response;
}

string interact_add(
    int sockfd, string url, string cookie, string auth_header
) {
    book_t book;
    book.read_to_add();
    string message = compute_post_request(
        IP, url, "/api/v1/tema/library/books",
        {book.to_json().dump()}, auth_header, cookie
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error")
        throw "interact_add() -> receive_from_server() error";
    return response;
}

string interact_delete(
    int sockfd, string url, string cookie, string auth_header
) {
    string message = compute_get_request(
        IP, url, auth_header, cookie
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error")
        throw "interact_delete() -> receive_from_server() error";
    return response;
}

string interact_logout(int sockfd, string cookie) {
    string message = compute_delete_request(
        IP, "/api/v1/tema/auth/logout", {cookie}
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error")
        throw "interact_logout() -> receive_from_server() error";
    return response;
}

// - - - - -

int main() {
    string command, response;
    int sockfd;
    
    while (1) {
        sockfd = open_connection(IP, PORT, AF_INET, SOCK_STREAM, 0);
        ASSERT(sockfd >= 0);
        getline(cin, command);

        if (command == "register") {
            response = interact_register(sockfd);

            optional<json_t> json_response = extract_json_response(response);
            if (json_response.has_value()) {
                string error_str = json_response.value()["error"].get<string>();
                cout << "[!] Error: " << error_str << endl;
            } else {
                cout << "[OK] Registered successfully!" << endl;
            }
        } else if (command == "login") {
            // TODO
        } else if (command == "enter_library") {
            // TODO
        } else if (command == "get_books") {
            // TODO
        } else if (command == "get_book") {
            // TODO
        } else if (command == "add_book") {
            // TODO
        } else if (command == "delete_book") {
            // TODO
        } else if (command == "logout") {
            // TODO
        } else if (command == "exit") {
            close_connection(sockfd);
            break;
        } else {
            cout << "[!] Error: Invalid command!" << endl;
            cout << "Valid commands are:" << endl;
            cout << "  register | login | enter_library | get_books |" << endl;
            cout << "  add_book | delete_book | logout | exit" << endl;
        }
        close_connection(sockfd);
    }

    return 0;
}
