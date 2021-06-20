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
    std::set<std::string> files;
    while((entity= readdir(dir))){
        if( strcmp(entity->d_name,".")!=0 ){
            std::string fname=entity->d_name;
            if(entity->d_type==DT_DIR)
                fname.push_back('/');
            files.insert(fname);
        }
    }
    closedir(dir);

    std::string res("<!DOCTYPE html>\n"
                    "<html>\n"
                    "<body>\n"
                    "<h1>Directory view</h1>\n"
                    "<table>\n"
                    "<tr><th>Name</th><th>Type</th><th>Size</th><th>Date modified</th></tr>\n");

    for(const std::string & f:files){
        std::string p=m_dirname;
        p.append(f);
        struct stat buf{};
        stat(p.c_str(),&buf);
        std::string type,size;
        std::string date(asctime(localtime(&buf.st_mtime)));
        if(f==".."){
            date="";
        }else if(S_ISDIR(buf.st_mode)) {
            type="D";
            size="-";
        }else if(S_ISREG(buf.st_mode)){
            type="F";
            size=std::to_string(buf.st_size);
        }else{
            type="U";
            size=std::to_string(buf.st_size);
        }
        res+=("<tr><td> <a href=\""+f+"\" title=\"\">"+f+"</a></td><td>"+type+"</td><td>"+size+"</td><td>"+date+"</td></tr>\n");
    }
    res+="</table>\n"
         "</body>\n"
         "</html>";
    Ok(req,res);
}

// Removes ../ from path
std::string normalizepath(const std::string &orig){
    std::stringstream ss(orig);
    std::string word;
    std::vector<std::string> vec;
    while(getline(ss,word,'/')){
        if(word==".."){
            if(vec.empty()||vec.back()=="..")
                vec.push_back(word);
            else
                vec.pop_back();
        }else{
            vec.push_back(word);
        }
    }
    std::string res;
    for(const auto &str:vec){
        res+=(str+"/");
    }
    return res;
}
// checks if basepath+subpath is inside basepath
bool isinside(const std::string& basepath, const std::string& subpath){
    std::string fullpath= normalizepath(basepath+subpath);
    return fullpath.find(basepath) == 0;
}


void DirectoryContent::handler(HTTPRequest& req) {
    if(req.GetMethod()!="GET"){
        NotImplemented(req);
        return;
    }

    if(req.GetURI()=="/"){
        showdirrectory(req);
    }else if(isinside(m_dirname,req.GetURI())){
        std::string subpath=m_dirname+req.GetURI();
        struct stat sb{};

        stat(subpath.c_str(), &sb);
        req.SetUri("/");
        if(S_ISDIR(sb.st_mode)) { // subpath is dirrectory
            DirectoryContent subdir(subpath);
            subdir.handler(req);
        }else if(S_ISREG(sb.st_mode)){ // subpath is file
            FileContent subfile(subpath);
            subfile.handler(req);
        }else{ // subpath not found
            NotFound(req);
        }
    }else{
        Forbidden(req);
    }
}
