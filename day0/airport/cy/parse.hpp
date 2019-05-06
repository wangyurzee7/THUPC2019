#ifndef PARSE_H
#define PARSE_H

#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

#define CHECK_OR_EXIT(expr) { \
    if (!(expr)) { \
        cerr << USAGE_MSG << endl; \
        exit(1); \
    } \
}

std::map<std::string, char*> parseArgs(int argc, char* argv[])
{
    std::map<std::string, char*> rst;

    for(int pos = 1; pos < argc;)
    {
        if (argv[pos][0] == '-') {
            if (argv[pos][1] == '-') {
                rst[argv[pos]+2] = argv[pos+1];
            } else {
                rst[argv[pos]+1] = argv[pos+1];
            }
            pos += 2;
        } else {
            rst[argv[pos]] = NULL;
            pos ++;
        }
    }

    return rst;
}

#endif // PARSE_H