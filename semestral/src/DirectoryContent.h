//
// Created by kostdani on 6/14/21.
//

#ifndef SERVER_DIRECTORYCONTENT_H
#define SERVER_DIRECTORYCONTENT_H

#include "ContentGenerator.h"
#include <dirent.h>
#include <set>
#include <sys/stat.h>
#include <string.h>
class DirectoryContent: public ContentGenerator{
public:
    DirectoryContent(std::string dirname);


    void handler(HTTPRequest msg) override;
private:
    std::string m_dirname;
};


#endif //SERVER_DIRECTORYCONTENT_H
