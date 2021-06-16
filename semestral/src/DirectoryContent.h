//
// Created by kostdani on 6/14/21.
//

#ifndef SERVER_DIRECTORYCONTENT_H
#define SERVER_DIRECTORYCONTENT_H

#include "ContentGenerator.h"
#include "FileContent.h"
#include <dirent.h>
#include <set>
#include <sys/stat.h>
#include <cstring>
class DirectoryContent: public ContentGenerator{
public:
    DirectoryContent(std::string dirname);

    void handler(HTTPRequest msg) override;

    bool multiplex(int epolld) override;
private:

    void showdirrectory(HTTPRequest msg);
    std::string m_dirname;
};


#endif //SERVER_DIRECTORYCONTENT_H
