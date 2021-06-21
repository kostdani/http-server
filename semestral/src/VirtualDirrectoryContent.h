//
// Created by kostdani on 6/14/21.
//

#ifndef SERVER_VIRTUALDIRRECTORYCONTENT_H
#define SERVER_VIRTUALDIRRECTORYCONTENT_H
#include "ContentGenerator.h"
/// Associates uri with other content generators
class VirtualDirrectoryContent:public ContentGenerator {
public:
    VirtualDirrectoryContent();
    /// Adds new location to map
    void AddLocation(const std::string &uri,ContentGenerator *generator);
    /// On request finds the longest suitable uri in map and resends message to corresponding generator
    void handler(HTTPRequest& msg) override;
protected:
    /// Map storing associations of urls with content generators
    std::map<std::string,ContentGenerator *> m_locations;
};


#endif //SERVER_VIRTUALDIRRECTORYCONTENT_H
