//
// Created by kostdani on 6/12/21.
//

#include "HTTPRequest.h"

std::string TimeStamp(){
    char tbuf[30];
    std::time_t t = std::time(nullptr);
    std::strftime(tbuf, 30, "%d/%b/%Y:%H:%M:%S %z", std::localtime(&t));
    return std::string (tbuf);
}

HTTPRequest::HTTPRequest(Logger* logger,Sender *sender,const std::string& host,const std::string& bytearray){
    m_sender=sender;
    m_logger=logger;
    m_host=host;
    m_date=TimeStamp();
    Parse(bytearray);
}

bool HTTPRequest::ParseHead(const std::string& head){
    std::stringstream str(head);
    m_request=head;
    getline(str,m_method,' ');
    getline(str,m_uri,' ');

    std::stringstream ss(m_uri);
    std::string noparamsuri;
    getline(ss,noparamsuri,'?');
    getline(ss,m_uriparams);
    m_uri=noparamsuri;

    getline(str,m_version,'\0');
    return true;
}
bool HTTPRequest::ParseHeader(const std::string& header){
    std::stringstream str(header);
    std::string key,val;
    getline(str,key,':');
    str>>std::skipws>>val;
    if(m_request_headers.find(key)!=m_request_headers.end())
        return false;
    m_request_headers[key]=val;
    return true;
}
bool HTTPRequest::Parse(const std::string& rawstring){

    std::stringstream str(rawstring);
    std::string head;
    getline(str,head,'\r');
    if(str.get()!='\n')
        return false;
    if(!ParseHead(head))
        return false;
    while(true){
        std::string header;
        getline(str,header,'\r');
        str.get();
        if(header.empty())
            break;
        if(!ParseHeader(header))
            return false;
    }

    m_uri=(GetHeader("Host")+m_uri);
    return true;
}

void HTTPRequest::Finish() {
    std::string res=m_version+" "+m_code+"\n";
    for(const auto& h:m_respond_headers){
        res+=(h.first+": "+h.second+"\n");
    }
    res+=("\n"+m_respond_body);
    m_sender->Push(res);
    std::string log=m_host+" "+m_ident+" "+m_authuser+" ["+m_date+"] \""+m_request+"\" "+m_code+" "+std::to_string(res.length());
    m_logger->Push(log);
}


std::string HTTPRequest::GetURI() const {
    return m_uri;
}
std::string HTTPRequest::GetMethod() const {
    return m_method;
}
std::string HTTPRequest::GetHeader(const std::string& key) const{
    auto it=m_request_headers.find(key);
    if(it==m_request_headers.end())
        return "";
    else
        return it->second;
}
void HTTPRequest::SetCode(const std::string& code) {
    m_code=code;
}
void HTTPRequest::SetBody(const std::string& body) {
    SetHeader("Content-Length",std::to_string(body.length()));
    m_respond_body=body;
}
void HTTPRequest::SetHeader(const std::string& key, const std::string& val) {
    m_respond_headers[key]=val;
}
void HTTPRequest::SetUri(const std::string& uri) {
    m_uri=uri;
}