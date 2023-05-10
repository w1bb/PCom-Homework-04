#ifndef _WI_REQUESTS_
#define _WI_REQUESTS_

#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::vector;
using std::stringstream;

#define HTTP_NL "\r\n"

// - - - - -

string compute_get_request(
    string host, string url,
    string header, string cookie
);

string compute_get_request(
    string host, string url,
    vector<string> cookies
);

// - - - - -

string compute_post_request(
    string host, string url, string content_type,
    vector<string> body_data, string header, string cookie
);

string compute_post_request(
    string host, string url, string content_type,
    vector<string> body_data, vector<string> cookies
);

// - - - - -

string compute_delete_request(
    string host, string url,
    string header, string cookie
);

string compute_delete_request(
    string host, string url,
    vector<string> cookies
);

#endif // _WI_REQUESTS_
