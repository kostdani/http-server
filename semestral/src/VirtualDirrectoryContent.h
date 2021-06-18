//
// Created by kostdani on 6/14/21.
//

#ifndef SERVER_VIRTUALDIRRECTORYCONTENT_H
#define SERVER_VIRTUALDIRRECTORYCONTENT_H
#include "ContentGenerator.h"

class VirtualDirrectoryContent:public ContentGenerator {
public:
    VirtualDirrectoryContent();

    void AddLocation(const std::string &location,ContentGenerator *generator);
    void handler(HTTPRequest& msg) override;
protected:
    std::map<std::string,ContentGenerator *> m_locations;
};


#endif //SERVER_VIRTUALDIRRECTORYCONTENT_H
