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
    std::stringstream str(rawstring);

    getline(str,method,' ');
    getline(str,uri,' ');
    getline(str,version,'\0');
    m_log.request=rawstring;
    return true;
}
bool HTTPRequest::AddHeader(std::string header){
    std::stringstream str(header);
    std::string key,val;
    getline(str,key,':');
    getline(str,val,'\n');
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
        if(str.get()!='\n')
            return false;
        if(header.empty()){
            return true;
        }
        AddHeader(header);
    }
}

void HTTPRequest::Finish() {
    std::string res=version;
    res.append(" ")
            .append(respond.code)
            .append("\n");
    for(auto h:respond.headers){
        res.append(h.first)
                .append(": ")
                .append(h.second)
                .append("\n");
    }
    res.append("\n")
            .append(respond.body);
    //std::cout<<"to sender: \n\n"<<res<<std::endl;
    m_sender->Push(res);

    std::string log;
    log.append(m_log.host)
    .append(" ")
    .append(m_log.ident)
    .append(" ")
    .append(m_log.authuser)
    .append(" [")
    .append(m_log.date)
    .append("] \"")
    .append(m_log.request)
    .append("\" ")
    .append(m_log.status)
    .append(" ")
    .append(m_log.bytes);
    //std::cout<<"tologger: "<<log<<std::endl;
    m_logger->Push(log);
}