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
    HTTPRequest(Logger *l= nullptr,Sender*s= nullptr,std::string host="-",std::string bytearray="");

    std::string GetHeader(const std::string& key);
    std::string GetURI() const;
    std::string GetMethod() const;


    void SetUri(std::string uri);
    void SetCode(std::string code);
    void SetHeader(std::string key,std::string val);
    void SetBody(std::string body);

    void Finish();
private:
    std::string l_date="-";
    std::string l_host="-";
    std::string l_ident="-";
    std::string l_authuser="-";

    std::string request;
    std::string uri;
    std::string method;
    std::string version;


    std::string code;
    std::string respond_body;
    std::map<std::string,std::string> request_headers;
    std::map<std::string,std::string> respond_headers;
    Logger *m_logger;
    Sender *m_sender;
    bool ParseHead();
    bool AddHeader(std::string header);
    bool Parse(std::string rawstring);

};


#endif //SERVER_HTTPREQUEST_H
