//
// Created by kostdani on 6/14/21.
//

#include "VirtualDirrectoryContent.h"

VirtualDirrectoryContent::VirtualDirrectoryContent() {

}

void VirtualDirrectoryContent::AddLocation(std::string location, ContentGenerator *generator) {
    m_locations[location]=generator;
}

// shortens path to next '/'
bool shortenpath(std::string& path){
    for(int i=path.length();i>=0;--i){
        if(path[i]=='/'){
            std::string npath(path.c_str(),i);
            path=npath;
            return true;
        }
    }
    return false;
}

void VirtualDirrectoryContent::handler(HTTPRequest req) {
    std::string url=req.uri;
    do{
        auto it=m_locations.find(url);
        if(it!=m_locations.end()){
            req.headers["Host"].append("/").append(url);
            std::string newuri(req.uri.c_str()+url.length());
            req.uri=newuri;
            it->second->Push(req);
            break;
        }
    }while(shortenpath(url));

}