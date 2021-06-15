//
// Created by kostdani on 6/12/21.
//

#include "HTTPRequest.h"


HTTPRequest::HTTPRequest(Logger* l,Sender *s,std::string bytearray){
    m_sender=s;
    m_logger=l;
Parse(bytearray);
}

bool HTTPRequest::ParseHead(std::string rawstring){
    m_log.request=rawstring;
    std::stringstream str(rawstring);

    getline(str,method,' ');
    getline(str,uri,' ');

    std::stringstream ss(uri);
    std::string noparamsuri;
    getline(ss,noparamsuri,'?');
    uri=noparamsuri;

    getline(str,version,'\0');
    respond.version=version;
    return true;
}
bool HTTPRequest::AddHeader(std::string header){
    std::stringstream str(header);
    std::string key,val;
    getline(str,key,':');
    str>>std::skipws>>val;
    //getline(str,val,'\n');
    headers[key]=val;
    return true;
}
bool HTTPRequest::Parse(std::string rawstring){
    char tbuf[30];
    std::time_t t = std::time(nullptr);
    std::strftime(tbuf, 30, "%d/%b/%Y:%H:%M:%S %z", std::localtime(&t));
    m_log.date=tbuf;

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
        AddHeader(header);
    }

    std::string host=headers["Host"];
    host.append(uri);
    uri=host;
    headers["Host"]="";
    return true;
}

void HTTPRequest::Finish() {
    std::string res=version+" "+respond.code+"\n";
    for(auto h:respond.headers){
        res+=(h.first+": "+h.second+"\n");
    }
    res+=("\n"+respond.body);
    m_sender->Push(res);
    std::string log=m_log.host+" "+m_log.ident+" "+m_log.authuser+" ["+m_log.date+"] \""+m_log.request+"\" "+m_log.status+" "+m_log.bytes;
    m_logger->Push(log);
}