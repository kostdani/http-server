//
// Created by kostdani on 6/19/21.
//

#ifndef SEMESTRAL_SCRIPTCONTENT_H
#define SEMESTRAL_SCRIPTCONTENT_H
#include "ContentGenerator.h"

class ScriptContent:public ContentGenerator {
public:
    ScriptContent(const std::string& filename);

    void handler(HTTPRequest& msg) override;
protected:
    std::string m_filename;
};



#endif //SEMESTRAL_SCRIPTCONTENT_H
