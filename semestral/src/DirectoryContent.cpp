//
// Created by kostdani on 6/14/21.
//

#include "DirectoryContent.h"

DirectoryContent::DirectoryContent(std::string dirname) {
    m_dirname=dirname;
}

void DirectoryContent::handler(HTTPRequest req) {

    DIR* dir= opendir(m_dirname.c_str());
    if(!dir)
        return;
    struct dirent* entity;
//        entity= readdir(dir);
    std::set<std::string> subfiles;
    while((entity= readdir(dir))){
        if( strcmp(entity->d_name,".") && strcmp(entity->d_name,"..")){
            std::string fname=entity->d_name;
            if(entity->d_type==DT_DIR)
                fname.append("/");
            subfiles.insert(fname);
        }

//            printf("%s\n",entity->d_name);
    }

    std::string res("<!DOCTYPE html>\n"
                    "<html>\n"
                    "<body>\n"
                    "\n"
                    "<h1>Directory view</h1>"
                    "<table>\n"
                    "<tr><th>Name</th><th>Date modified</th></tr>\n");

    for(auto s:subfiles){
        std::string p=m_dirname;
        p.append(s);
        struct stat buf;
        stat(p.c_str(),&buf);

        char *date = asctime(localtime(&buf.st_mtime));
        res.append("<tr><td>")
                .append(s)
                .append("</td><td>")
                .append(date,strlen(date)-1)
                .append("</td></tr>\n");
        //            printf("%s : %s",s.c_str(),date);
        //printf("\n %s\n", date);
    }
    res.append("</table>\n"
               "</body>\n"
               "</html>");
    closedir(dir);
    req.respond.version=req.version;
    req.respond.code="200 OK";
    req.respond.body=res;
    req.respond.headers["Content-Length"]=std::to_string(res.length());

    req.m_log.status="200";
    req.m_log.bytes=std::to_string(res.length());
    req.Finish();
}