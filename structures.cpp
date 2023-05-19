// Copyright Valentin-Ioan Vintila 2023.
// All rights reserved.

#include "structures.hpp"

// - - - - -

void credentials_t::read() {
    cout << "username="; (cin >> user).ignore();
    cout << "password="; (cin >> pass).ignore();
}

json_t credentials_t::to_json() const {
    json_t credentials_json = {
        {"username", user},
        {"password", pass}
    };
    return credentials_json;
}

// - - - - -

void book_t::read_to_add() {
    cout << "title="; getline(cin, title);
    cout << "author="; getline(cin, author);
    cout << "genre="; getline(cin, genre);
    cout << "publisher="; getline(cin, publisher);
    cout << "page_count="; (cin >> page_count).ignore();
}

json_t book_t::to_json() const {
    json_t book_json = {
        {"title", title},
        {"author", author},
        {"genre", genre},
        {"publisher", publisher},
        {"page_count", page_count}
    };
    return book_json;
}

// - - - - -

optional<json_t> extract_json_response(string response) {
    response = response.substr(response.find("\r\n\r\n") + 4);
    if (response == "") return {};
    return json_t::parse(response);
}

string extract_cookie(string response) {
    size_t start = response.find("\r\nSet-Cookie: ") + 14;
    size_t end = response.find(' ', start);
    response = response.substr(start, end-start);
    return response.substr(0, response.find("; "));
}

string extract_jwt_token(string response) {
    response = response.substr(response.find("\r\n\r\n") + 4);
    json_t json = json_t::parse(response);
    if (json["token"].is_null())
        return "";
    return json["token"].get<string>();
}
