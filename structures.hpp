#ifndef _WI_STRUCTURES_HPP_
#define _WI_STRUCTURES_HPP_

#include <iostream>
#include <string>

#include "nlohmann/json.hpp"

using std::string;
using std::cout;
using std::cin;

using json_t = nlohmann::json;

// - - - - -

struct credentials_t {
    string user;
    string pass;

    void read();
    json_t to_json() const;
};

// - - - - -

struct book_t {
    int id;
    string title;
    string author;
    string genre;
    string publisher;
    int page_count;

    void read_to_add();
    json_t to_json() const;
};

#endif // _WI_STRUCTURES_HPP_
