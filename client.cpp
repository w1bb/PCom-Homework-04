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

string interact_access(int sockfd, string cookie) {
    string message = compute_get_request(
        IP, "/api/v1/tema/library/access", {cookie}
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error")
        throw "interact_access() -> receive_from_server() error";
    return response;
}

string interact_books(int sockfd, string cookie, string auth_header) {
    string message = compute_get_request(
        IP, "/api/v1/tema/library/books", auth_header, cookie
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error")
        throw "interact_books() -> receive_from_server() error";
    return response;
}

string interact_book(int sockfd, string id, string cookie, string auth_header) {
    string message = compute_get_request(
        IP, "/api/v1/tema/library/books/" + id, auth_header, cookie
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error")
        throw "interact_book() -> receive_from_server() error";
    return response;
}

string interact_add(
    int sockfd, string cookie, string auth_header
) {
    book_t book;
    book.read_to_add();
    string message = compute_post_request(
        IP, "/api/v1/tema/library/books", "application/json",
        {book.to_json().dump()}, auth_header, cookie
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error")
        throw "interact_add() -> receive_from_server() error";
    return response;
}

string interact_delete(
    int sockfd, string id, string cookie, string auth_header
) {
    string message = compute_delete_request(
        IP, "/api/v1/tema/library/books/" + id, auth_header, cookie
    );
    send_to_server(sockfd, message);

    string response = receive_from_server(sockfd);
    if (response == "error")
        throw "interact_delete() -> receive_from_server() error";
    return response;
}

string interact_logout(int sockfd, string cookie) {
    string message = compute_get_request(
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
    string command, response, cookie, jwt;
    int sockfd;

    bool logged_in = false;
    bool library_access = false;
    
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
            if (logged_in) {
                cout << "[!] Error: The user is already logged in!" << endl;
            } else {
                response = interact_login(sockfd);
                optional<json_t> json_response = extract_json_response(response);
                if (json_response.has_value()) {
                    string error_str = json_response.value()["error"].get<string>();
                    cout << "[!] Error: " << error_str << endl;
                } else {
                    logged_in = true;
                    cookie = extract_cookie(response);
                    cout << "[OK] Logged in - welcome!" << endl;
                }
            }
        } else if (command == "enter_library") {
            if (!logged_in) {
                cout << "[!] Error: Please login before entering the library!" << endl;
            } else {
                response = interact_access(sockfd, cookie);
                optional<json_t> json_response = extract_json_response(response);
                if (json_response.has_value() &&
                    !json_response.value()["error"].is_null()) {
                    string error_str = json_response.value()["error"].get<string>();
                    cout << "[!] Error: " << error_str << endl;
                } else {
                    cout << "[OK] Welcome to the library!" << endl;
                    library_access = true;
                    jwt = extract_jwt_token(response);
                    cout << "^- Token: " << jwt << endl;
                }
            }
        } else if (command == "get_books") {
            if (!logged_in) {
                cout << "[!] Error: Please login (and enter the library) before getting books!" << endl;
            } else if (!library_access) {
                cout << "[!] Error: Please enter the library before getting books!" << endl;
            } else {
                response = interact_books(sockfd, cookie, "Authorization: Bearer " + jwt);
                optional<json_t> json_response = extract_json_response(response);
                if (json_response.has_value() &&
                    !json_response.value().is_array() &&
                    !json_response.value()["error"].is_null()) {
                    string error_str = json_response.value()["error"].get<string>();
                    cout << "[!] Error: " << error_str << endl;
                } else {
                    cout << "[OK] Here is the list of books we've collected:" << endl;
                    bool any_book = false;
                    for (auto book : json_response.value()) {
                        cout << "(id: " << book["id"];
                        cout << ") " << book["title"].get<string>() << endl;
                        any_book = true;
                    }
                    if (!any_book) {
                        cout << "^- The list is empty!" << endl;
                    }
                }
            }
        } else if (command == "get_book") {
            if (!logged_in) {
                cout << "[!] Error: Please login (and enter the library) before getting a book!" << endl;
            } else if (!library_access) {
                cout << "[!] Error: Please enter the library before getting a book!" << endl;
            } else {
                string id;
                cout << "id="; getline(cin, id);
                while (!is_number(id)) {
                    cout << "[!] The ID you provided is not a valid number! Please try again!" << endl;
                    cout << "id="; getline(cin, id);
                }
                response = interact_book(sockfd, id, cookie, "Authorization: Bearer " + jwt);
                optional<json_t> json_response = extract_json_response(response);
                if (json_response.has_value() &&
                    !json_response.value()["error"].is_null()) {
                    string error_str = json_response.value()["error"].get<string>();
                    cout << "[!] Error: " << error_str << endl;
                    cout << "    ^-: This usually means the ID is not present in the database!" << endl;
                } else {
                    cout << "[OK] Here are the details about the book you requested:" << endl;
                    cout << "ID: " << json_response.value()["id"] << endl;
                    cout << "Title: " << json_response.value()["title"].get<string>() << endl;
                    cout << "Author: " << json_response.value()["author"].get<string>() << endl;
                    cout << "Publisher: " << json_response.value()["publisher"].get<string>() << endl;
                    cout << "Genre: " << json_response.value()["genre"].get<string>() << endl;
                    cout << "Pages: " << json_response.value()["page_count"] << endl;
                }
            }
        } else if (command == "add_book") {
            if (!logged_in) {
                cout << "[!] Error: Please login (and enter the library) before adding books!" << endl;
            } else if (!library_access) {
                cout << "[!] Error: Please enter the library before adding books!" << endl;
            } else {
                response = interact_add(sockfd, cookie, "Authorization: Bearer " + jwt);
                optional<json_t> json_response;// = extract_json_response(response);
                if (json_response.has_value() &&
                    !json_response.value()["error"].is_null()) {
                    string error_str = json_response.value()["error"].get<string>();
                    cout << "[!] Error: " << error_str << endl;
                } else {
                    cout << "[OK] Book added successfully!" << endl;
                }
            }
        } else if (command == "delete_book") {
            if (!logged_in) {
                cout << "[!] Error: Please login (and enter the library) before deleting books!" << endl;
            } else if (!library_access) {
                cout << "[!] Error: Please enter the library before deleting books!" << endl;
            } else {
                string id;
                cout << "id="; getline(cin, id);
                while (!is_number(id)) {
                    cout << "[!] The ID you provided is not a valid number! Please try again!" << endl;
                    cout << "id="; getline(cin, id);
                }
                response = interact_delete(sockfd, id, cookie, "Authorization: Bearer " + jwt);
                optional<json_t> json_response = extract_json_response(response);
                if (json_response.has_value() &&
                    !json_response.value()["error"].is_null()) {
                    string error_str = json_response.value()["error"].get<string>();
                    cout << "[!] Error: " << error_str << endl;
                    cout << "    ^-: This usually means the ID is not present in the database!" << endl;
                } else {
                    cout << "[OK] Book deleted successfully!" << endl;
                }
            }
        } else if (command == "logout") {
            if (!logged_in) {
                cout << "[!] Error: Nobody to log out!" << endl;
            } else {
                response = interact_logout(sockfd, cookie);
                optional<json_t> json_response = extract_json_response(response);
                if (json_response.has_value()) {
                    string error_str = json_response.value()["error"].get<string>();
                    cout << "[!] Error: " << error_str << endl;
                } else {
                    jwt.clear();
                    cookie.clear();
                    logged_in = false;
                    library_access = false;
                    cout << "[OK] Logged out - goodbye!" << endl;
                }
            }
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
