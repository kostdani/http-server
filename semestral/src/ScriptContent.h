//
// Created by kostdani on 6/14/21.
//

#ifndef SERVER_SCRIPTCONTENT_H
#define SERVER_SCRIPTCONTENT_H
#include "ContentGenerator.h"

class ScriptContent: public ContentGenerator{
public:
    ScriptContent(std::string scriptname);


    void handler(HTTPRequest msg) override;
private:
    std::string m_scriptname;
};


#endif //SERVER_SCRIPTCONTENT_H
