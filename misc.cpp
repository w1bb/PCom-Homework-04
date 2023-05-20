// Copyright Valentin-Ioan Vintila 2023.
// All rights reserved.

#include "misc.hpp"

std::ostringstream assert_oss;

bool is_number(const string& s) {
    return !s.empty() && std::find_if(
        s.begin(), 
        s.end(),
        [](unsigned char c) {
            return !std::isdigit(c);
        }
    ) == s.end();
}