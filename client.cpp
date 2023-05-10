// TOOD - modify
#include <bits/stdc++.h>

// Include JSON support
#include "nlohmann/json.hpp"

// Include helper headers
#include "structures.hpp"
#include "requests.hpp"
#include "helpers.hpp"
#include "buffer.hpp"

// - - - - -

using namespace std;

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
    if (response == "error") {
        // TODO - throw
    }
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
    if (response == "error") {
        // TODO - throw
    }
    return response;
}

string interact_access(int sockfd, string url, string cookie) {
    string message = compute_get_request(
        IP, url, {cookie}
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error") {
        // TODO - throw
    }
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
    if (response == "error") {
        // TODO - throw
    }
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
    if (response == "error") {
        // TODO - throw
    }
    return response;
}

string interact_logout(int sockfd, string cookie) {
    string message = compute_delete_request(
        IP, "/api/v1/tema/auth/logout", {cookie}
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error") {
        // TODO - throw
    }
    return response;
}

int main() {
    return 0;
}
