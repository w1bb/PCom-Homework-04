// Copyright Valentin-Ioan Vintila 2023.
// All rights reserved.

#include "requests.hpp"

string compute_get_request(
    string host, string url,
    string header, string cookie
) {
    stringstream sout;

    sout << "GET " << url << " HTTP/1.1" << HTTP_NL;
    sout << "Host: " << host << HTTP_NL;
    sout << header << HTTP_NL;
    sout << "Cookie: " << cookie << HTTP_NL;

    sout << HTTP_NL;
    return sout.str();
}

string compute_get_request(
    string host, string url,
    vector<string> cookies
) {
    stringstream sout;

    sout << "GET " << url << " HTTP/1.1" << HTTP_NL;
    sout << "Host: " << host << HTTP_NL;
    sout << "Cookie: ";
    for (string& cookie : cookies)
        sout << cookie << ';';
    sout.seekp(-1, std::ios_base::end);

    sout << HTTP_NL << HTTP_NL;
    return sout.str();
}

// - - - - -

string compute_post_request(
    string host, string url, string content_type,
    vector<string> body_data
) {
    stringstream sout;

    sout << "POST " << url << " HTTP/1.1" << HTTP_NL;
    sout << "Host: " << host << HTTP_NL;
    sout << "Content-Type: " << content_type << HTTP_NL;

    string body;
    for (string& field : body_data)
        (body += field).push_back('&');
    body.pop_back();
    sout << "Content-Length: " << body.size() << HTTP_NL;
    
    sout << HTTP_NL << body;    
    return sout.str();
}

string compute_post_request(
    string host, string url, string content_type,
    vector<string> body_data, string header, string cookie
) {
    stringstream sout;

    sout << "POST " << url << " HTTP/1.1" << HTTP_NL;
    sout << "Host: " << host << HTTP_NL;
    sout << "Content-Type: " << content_type << HTTP_NL;

    string body;
    for (string& field : body_data)
        (body += field).push_back('&');
    body.pop_back();
    sout << "Content-Length: " << body.size() << HTTP_NL;
    sout << header << HTTP_NL;
    sout << "Cookie: " << cookie << HTTP_NL;
    
    sout << HTTP_NL << body;    
    return sout.str();
}

string compute_post_request(
    string host, string url, string content_type,
    vector<string> body_data, vector<string> cookies
) {
    stringstream sout;

    sout << "POST " << url << " HTTP/1.1" << HTTP_NL;
    sout << "Host: " << host << HTTP_NL;
    sout << "Content-Type: " << content_type << HTTP_NL;

    string body;
    for (string& field : body_data)
        (body += field).push_back('&');
    body.pop_back();
    sout << "Content-Length: " << body.size() << HTTP_NL;
    sout << "Cookie: ";
    for (string& cookie : cookies)
        sout << cookie << ';';
    sout.seekp(-1, std::ios_base::end);
    
    sout << HTTP_NL << HTTP_NL << body;    
    return sout.str();
}

// - - - - -

string compute_delete_request(
    string host, string url,
    string header, string cookie
) {
    stringstream sout;

    sout << "DELETE " << url << " HTTP/1.1" << HTTP_NL;
    sout << "Host: " << host << HTTP_NL;
    sout << header << HTTP_NL;
    sout << "Cookie: " << cookie << HTTP_NL;

    sout << HTTP_NL;
    return sout.str();
}

string compute_delete_request(
    string host, string url,
    vector<string> cookies
) {
    stringstream sout;

    sout << "DELETE " << url << " HTTP/1.1" << HTTP_NL;
    sout << "Host: " << host << HTTP_NL;
    sout << "Cookie: ";
    for (string& cookie : cookies)
        sout << cookie << ';';
    sout.seekp(-1, std::ios_base::end);

    sout << HTTP_NL << HTTP_NL;
    return sout.str();
}
