//
// Created by kostdani on 6/12/21.
//

#include "HTTPRequest.h"


HTTPRequest::HTTPRequest(std::string bytearray){
Parse(bytearray);
}

bool HTTPRequest::ParseHead(std::string rawstring){
    std::stringstream str(rawstring);

    getline(str,method,' ');
    getline(str,uri,' ');
    getline(str,version,'\n');
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
    std::stringstream str(rawstring);
    std::string head;
    getline(str,head,'\n');
    if(!ParseHead(head))
        return false;
    while(true){
        std::string header;
        getline(str,header,'\n');
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
    std::cout<<res<<std::endl;
}