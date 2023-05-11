// Copyright Valentin-Ioan Vintila 2023.
// All rights reserved.

#ifndef _WI_BUFFER_H_
#define _WI_BUFFER_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

// - - - - -

struct buffer_t {
    char *data;
    size_t size;

    buffer_t();

    // - - - - -

    buffer_t& init();
    void destroy();
    bool empty() const;
    void append(const char *new_data, size_t new_data_size);

    int find(const char *search_data, size_t search_data_size);
    int find_insensitive(const char *search_data, size_t search_data_size);
};

#endif // _WI_BUFFER_H_
