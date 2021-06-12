//
// Created by kostdani on 6/12/21.
//

#ifndef SERVER_HTTPREQUEST_H
#define SERVER_HTTPREQUEST_H
#include "HTTPRespond.h"
#include <string>
#include <sstream>
#include <map>

class HTTPRequest {
public:
    HTTPRequest(std::string bytearray);

    bool ParseHead(std::string rawstring);
    bool AddHeader(std::string header);
    bool Parse(std::string rawstring);

    std::string method;
    std::string uri;
    std::string version;
    std::map<std::string,std::string> headers;
    HTTPRespond respond;
};


#endif //SERVER_HTTPREQUEST_H
