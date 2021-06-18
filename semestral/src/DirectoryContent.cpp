//
// Created by kostdani on 6/14/21.
//

#include "DirectoryContent.h"

DirectoryContent::DirectoryContent(const std::string& dirname):ContentGenerator(), m_dirname(dirname) {}

void DirectoryContent::showdirrectory(HTTPRequest& req) {

    DIR* dir= opendir(m_dirname.c_str());
    if(!dir)
        return;
    struct dirent* entity;
    std::set<std::string> subfiles;
    while((entity= readdir(dir))){
        if( strcmp(entity->d_name,".") && strcmp(entity->d_name,"..")){
            std::string fname=entity->d_name;
            if(entity->d_type==DT_DIR)
                fname.append("/");
            subfiles.insert(fname);
        }
    }

    std::string res("<!DOCTYPE html>\n"
                    "<html>\n"
                    "<body>\n"
                    "\n"
                    "<h1>Directory view</h1>"
                    "<table>\n"
                    "<tr><th>Name</th><th>Type</th><th>Size</th><th>Date modified</th></tr>\n");

    for(auto s:subfiles){
        std::string p=m_dirname;
        p.append(s);
        struct stat buf;
        stat(p.c_str(),&buf);
        std::string type,size;
        if(S_ISDIR(buf.st_mode)) {
            type="D";
            size="-";
        }else if(S_ISREG(buf.st_mode)){
            type="F";
            size=std::to_string(buf.st_size);
        }else{
            type="U";
            size=std::to_string(buf.st_size);
        }

        std::string date(asctime(localtime(&buf.st_mtime)));
        res+=("<tr><td> <a href=\""+s+="\" title=\"\">"+s+"</a></td><td>"+type+"</td><td>"+size+"</td><td>"+date+"</td></tr>\n");
    }
    res+="</table>\n"
         "</body>\n"
         "</html>";
    closedir(dir);
    Ok(req,res);
}

void DirectoryContent::handler(HTTPRequest& req) {
    if(req.GetMethod()!="GET"){
        NotImplemented(req);
        return;
    }

    if(req.GetURI()=="/"){
        showdirrectory(req);
    }else{
        std::string subpath=m_dirname;
        subpath.append(req.GetURI());
        struct stat sb;

        if (stat(subpath.c_str(), &sb) == 0 ){
            req.SetUri("/");
            if(S_ISDIR(sb.st_mode)) {
                DirectoryContent subdir(subpath);
                subdir.Push(req);
                subdir.onInput(0);
                return;
            }else if(S_ISREG(sb.st_mode)){
                FileContent subfile(subpath);
                subfile.Push(req);
                subfile.onInput(0);
                return;
            }
        }

        NotFound(req);
    }
}

bool DirectoryContent::multiplex(int epolld) {

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN ;

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;
}