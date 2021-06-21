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
#include <algorithm>

/// Class storing data about HTTP request
class HTTPRequest {
public:
    HTTPRequest()=default;

    HTTPRequest(Logger *l,Sender*s,const std::string& host,const std::string& bytearray);

    /// Returns value of request header by key
    std::string GetHeader(const std::string& key) const;
    /// Returns uri
    std::string GetURI() const;
    /// Returns method of request
    std::string GetMethod() const;
    /// Returns params from uri (query string)
    std::string GetParams() const;

    /// Sets uri
    void SetUri(const std::string& uri);
    /// Sets status code of respond
    void SetCode(const std::string& code);
    /// Sets/adds respond header
    void SetHeader(const std::string& key,const std::string& val);
    /// Sets respond body
    void SetBody(const std::string& body);

    /// Finishes work with request
    /// Sends what is ready to sender and logger
    void Finish();
private:
    /// Date, time, and time zone that the request was received
    std::string m_date;
    /// IP address of the client (remote host) which made the request to the server
    std::string m_host="-";
    std::string m_ident="-";
    std::string m_authuser="-";
    /// Request line from the client (method, uri, version)
    std::string m_request;
    /// Request uri for server use
    std::string m_uri;
    /// Part of uri after '?'
    std::string m_uriparams;
    /// Request method
    std::string m_method;
    /// Request version
    std::string m_version;
    /// Respond status code
    std::string m_code;
    /// Respond body
    std::string m_respond_body;
    /// Request headers
    std::map<std::string,std::string> m_request_headers;
    /// Respond headers
    std::map<std::string,std::string> m_respond_headers;
    /// Logger to send log
    Logger *m_logger;
    /// Sender to send respond
    Sender *m_sender;

    /// Parses request line
    bool ParseHead(const std::string& head);
    /// Parses header
    bool ParseHeader(const std::string& header);
    /// Parses full request
    bool Parse(const std::string& rawstring);

};


#endif //SERVER_HTTPREQUEST_H
