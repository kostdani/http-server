//
// Created by kostdani on 6/12/21.
//

#ifndef SERVER_HTTPREQUEST_H
#define SERVER_HTTPREQUEST_H
#include "Sender.h"
#include "Logger.h"
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <ctime>
class HTTPRequest {
public:
    HTTPRequest(Logger *l= nullptr,Sender*s= nullptr,std::string bytearray="");

    void SetCode(int code);


    void Finish();
    std::string method;
    std::string uri;
    std::string version;
    std::map<std::string,std::string> headers;
    class HTTPRespond {
    public:
        HTTPRespond(){}

        std::string code;
        std::string version;
        std::map<std::string,std::string> headers;
        std::string body;
    };
    HTTPRespond respond;
    class HTTPLog {
    public:
        HTTPLog(){}

        std::string host="-";
        std::string ident="-";
        std::string authuser="-";
        std::string date="-";
        std::string request="-";
        std::string status="-";
        std::string bytes="-";
    };
    HTTPLog m_log;
private:
    Logger *m_logger;
    Sender *m_sender;
    bool ParseHead(std::string rawstring);
    bool AddHeader(std::string header);
    bool Parse(std::string rawstring);

};


#endif //SERVER_HTTPREQUEST_H
