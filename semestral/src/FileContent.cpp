//
// Created by kostdani on 6/13/21.
//

#include "FileContent.h"


FileContent::FileContent(const std::string& filename):ContentGenerator(), m_filename(filename) {}

 void FileContent::handler(HTTPRequest& req) {
     if(req.GetMethod()!="GET"){
         NotImplemented(req);
         return;
     }

     struct stat buf{};
     if(req.GetURI()=="/" && stat(m_filename.c_str(),&buf)==0){
         std::ifstream infile {m_filename };
         std::string file_contents { std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };
         Ok(req,file_contents);
     }else {
         NotFound(req);
     }
}