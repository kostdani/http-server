//
// Created by kostdani on 6/12/21.
//

#ifndef SERVER_HTTPRESPOND_H
#define SERVER_HTTPRESPOND_H
#include <string>
#include <map>

class HTTPRespond {
public:
    HTTPRespond(){}

    std::string code;
    std::string version;
    std::map<std::string,std::string> headers;
    std::string body;
};


#endif //SERVER_HTTPRESPOND_H
