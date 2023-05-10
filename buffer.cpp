#include "buffer.hpp"

// - - - - -

buffer_t::buffer_t() : data(NULL), size(0) {}

buffer_t& buffer_t::init() {
    data = NULL;
    size = 0;
    return *this;
}

void buffer_t::destroy() {
    if (data != NULL)
        free(data);
    init();
}

bool buffer_t::empty() const {
    return (data == NULL);
}

void buffer_t::append(const char *new_data, size_t new_data_size) {
    if (data)
        data = (char *)realloc(data, (size + new_data_size) * sizeof(char));
    else
        data = (char *)calloc(new_data_size, sizeof(char));
    memcpy(data + size, new_data, new_data_size);
    size += new_data_size;
}

int buffer_t::find(const char *search_data, size_t search_data_size) {
    if (search_data_size > size)
        return -1;
    size_t last_pos = size - search_data_size + 1;
    for (size_t i = 0; i < last_pos; ++i) {
        size_t j;
        for (j = 0; j < search_data_size; ++j)
            if (data[i + j] != search_data[j])
                break;
        if (j == search_data_size)
            return i;
    }
    return -1;
}

int buffer_t::find_insensitive(const char *search_data, size_t search_data_size) {
    if (search_data_size > size)
        return -1;
    size_t last_pos = size - search_data_size + 1;
    for (size_t i = 0; i < last_pos; ++i) {
        size_t j;
        for (j = 0; j < search_data_size; ++j)
            if (tolower(data[i + j]) != tolower(search_data[j]))
                break;
        if (j == search_data_size)
            return i;
    }
    return -1;
}
