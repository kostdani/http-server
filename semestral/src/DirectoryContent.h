//
// Created by kostdani on 6/14/21.
//

#ifndef SERVER_DIRECTORYCONTENT_H
#define SERVER_DIRECTORYCONTENT_H
#include "ContentGenerator.h"
#include "FileContent.h"
#include "ScriptContent.h"
#include <dirent.h>
#include <set>
#include <sys/stat.h>
#include <cstring>
/// Content generator associated with dirrectory
class DirectoryContent: public ContentGenerator{
public:
    DirectoryContent(const std::string& dirname);

    void handler(HTTPRequest& msg) override;
private:
    /// Respond to the request with html page listing the directory content
    void ShowDirectory(HTTPRequest& msg);
    /// Directory path
    std::string m_dirname;
};


#endif //SERVER_DIRECTORYCONTENT_H
