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
    json_t credentials_json = {
        {"title", title},
        {"author", author},
        {"genre", genre},
        {"publisher", publisher},
        {"page_count", page_count}
    };
}
