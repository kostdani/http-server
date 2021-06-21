//
// Created by kostdani on 6/14/21.
//

#include "VirtualDirrectoryContent.h"

VirtualDirrectoryContent::VirtualDirrectoryContent() {

}

void VirtualDirrectoryContent::AddLocation(const std::string& location, ContentGenerator *generator) {
    m_locations[location]=generator;
}

// shortens path to next '/' for example /dir/subdir -> /dir
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

void VirtualDirrectoryContent::handler(HTTPRequest& req) {
    if(req.Malformed()){
        BadRequest(req);
        return;
    }
    std::string url=req.GetURI();
    do{
        auto it=m_locations.find(url);
        if(it!=m_locations.end()){
            std::string newuri(req.GetURI().c_str()+url.length());
            if(newuri.empty())
                newuri="/";
            req.SetUri(newuri);
            it->second->Push(req);
            return;
        }
    }while(shortenpath(url));

    NotFound(req);
}