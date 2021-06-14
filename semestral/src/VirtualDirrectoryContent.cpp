//
// Created by kostdani on 6/14/21.
//

#include "VirtualDirrectoryContent.h"

VirtualDirrectoryContent::VirtualDirrectoryContent() {

}

void VirtualDirrectoryContent::AddLocation(std::string location, ContentGenerator *generator) {
    m_locations[location]=generator;
}

void VirtualDirrectoryContent::handler(HTTPRequest req) {
    std::string loc;
    std::stringstream uristream(req.uri);
    getline(uristream,loc,'/');
    if(loc.empty()){
        printf("empty loc\n");
        return;
    }else{
        auto it=m_locations.find(loc);
        if(it==m_locations.end()){
            printf("not found location\n");
            return;
        }

        req.headers["Host"].append("/").append(loc);
        std::string cuturi;
        getline(uristream,cuturi,'\0');
        req.uri=cuturi;
        it->second->Push(req);
    }
}