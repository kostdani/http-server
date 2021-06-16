//
// Created by kostdani on 6/13/21.
//

#ifndef SERVER_FILECONTENT_H
#define SERVER_FILECONTENT_H
#include "ContentGenerator.h"
#include <fstream>

/// Content generator associated with file
class FileContent: public ContentGenerator{
public:
    FileContent(std::string filename);

    void handler(HTTPRequest msg) override;
private:
    std::string m_filename;
};


#endif //SERVER_FILECONTENT_H
