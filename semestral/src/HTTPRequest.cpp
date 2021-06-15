//
// Created by kostdani on 6/12/21.
//

#include "HTTPRequest.h"


HTTPRequest::HTTPRequest(Logger* l,Sender *s,std::string h,std::string bytearray){
    m_sender=s;
    m_logger=l;
    l_host=h;
    char tbuf[30];
    std::time_t t = std::time(nullptr);
    std::strftime(tbuf, 30, "%d/%b/%Y:%H:%M:%S %z", std::localtime(&t));
    l_date=tbuf;
    Parse(bytearray);
}

bool HTTPRequest::ParseHead(){
    std::stringstream str(request);

    getline(str,method,' ');
    getline(str,uri,' ');

    std::stringstream ss(uri);
    std::string noparamsuri;
    getline(ss,noparamsuri,'?');
    uri=noparamsuri;

    getline(str,version,'\0');
    return true;
}
bool HTTPRequest::AddHeader(std::string header){
    std::stringstream str(header);
    std::string key,val;
    getline(str,key,':');
    str>>std::skipws>>val;
    request_headers[key]=val;
    return true;
}
bool HTTPRequest::Parse(std::string rawstring){

    std::stringstream str(rawstring);
    getline(str,request,'\r');
    if(str.get()!='\n')
        return false;
    if(!ParseHead())
        return false;
    while(true){
        std::string header;
        getline(str,header,'\r');
        str.get();
        if(header.empty())
            break;
        AddHeader(header);
    }

    std::string host=request_headers["Host"];
    uri=(host+uri);
    return true;
}

void HTTPRequest::Finish() {
    std::string res=version+" "+code+"\n";
    for(auto h:respond_headers){
        res+=(h.first+": "+h.second+"\n");
    }
    res+=("\n"+respond_body);
    m_sender->Push(res);
    std::string log=l_host+" "+l_ident+" "+l_authuser+" ["+l_date+"] \""+request+"\" "+code+" "+std::to_string(res.length());
    m_logger->Push(log);
}


std::string HTTPRequest::GetURI() const {
    return uri;
}
std::string HTTPRequest::GetMethod() const {
    return method;
}
std::string HTTPRequest::GetHeader(const std::string& key) {
    return request_headers[key];
}
void HTTPRequest::SetCode(std::string c) {
    code=c;
}
void HTTPRequest::SetBody(std::string body) {
    SetHeader("Content-Length",std::to_string(body.length()));
    respond_body=body;
}
void HTTPRequest::SetHeader(std::string key, std::string val) {
    respond_headers[key]=val;
}
void HTTPRequest::SetUri(std::string u) {
    uri=u;
}