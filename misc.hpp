#ifndef _WI_MISC_HPP_
#define _WI_MISC_HPP_

#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <cstdio>
#include <ctime>

extern std::ostringstream assert_oss;

#define ASSERT(n) \
    do { \
        using namespace std; \
        if(!(n)) { \
            using namespace std::chrono; \
            auto now = system_clock::now(); \
            auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000; \
            auto timer = system_clock::to_time_t(now); \
            tm bt = *std::localtime(&timer); \
            assert_oss << std::put_time(&bt, "%H:%M:%S"); \
            cerr << "'" << #n << "' -> failed!" << endl; \
            cerr << "Time: " << assert_oss.str() << endl; \
            cerr << "File: " << __FILE__ << " (line: " << __LINE__ << ")" << endl; \
            exit(EXIT_FAILURE); \
        } \
    } while (0);

#endif // _WI_MISC_HPP_
