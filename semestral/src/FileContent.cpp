//
// Created by kostdani on 6/13/21.
//

#include "FileContent.h"


FileContent::FileContent(std::string filename):ContentGenerator() {
    m_filename=filename;
}
 void FileContent::handler(HTTPRequest req) {
             if(req.uri=="/"){
                 req.respond.version=req.version;
                 req.respond.code="200 OK";
                 std::ifstream infile {m_filename };
                 std::string file_contents { std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };
                 req.respond.headers["Content-Length"]=std::to_string(file_contents.length());
                 req.respond.body=file_contents;
                 req.Finish();
                 //std::cout<<file_contents<<std::endl;
             }else {
                 printf("not implemented\n");
             }

}