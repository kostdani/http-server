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
    HTTPRequest()=default;

    HTTPRequest(Logger *l,Sender*s,const std::string& host,const std::string& bytearray);

    std::string GetHeader(const std::string& key) const;
    std::string GetURI() const;
    std::string GetMethod() const;


    void SetUri(const std::string& uri);
    void SetCode(const std::string& code);
    void SetHeader(const std::string& key,const std::string& val);
    void SetBody(const std::string& body);

    void Finish();
private:
    std::string m_date="-";
    std::string m_host="-";
    std::string m_ident="-";
    std::string m_authuser="-";
    std::string m_request;
    std::string m_uri;
    std::string m_uriparams;
    std::string m_method;
    std::string m_version;
    std::string m_code;
    std::string m_respond_body;
    std::map<std::string,std::string> m_request_headers;
    std::map<std::string,std::string> m_respond_headers;
    Logger *m_logger;
    Sender *m_sender;

    bool ParseHead(const std::string& head);
    bool ParseHeader(const std::string& header);
    bool Parse(const std::string& rawstring);

};


#endif //SERVER_HTTPREQUEST_H
