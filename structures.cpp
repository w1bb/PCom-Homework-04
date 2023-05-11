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
    // cout << ">>> " << response << " <<<" << std::endl;
    if (response == "") return {};
    return json_t::parse(response);
}
