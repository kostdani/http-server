//
// Created by kostdani on 6/13/21.
//

#include "FileContent.h"


FileContent::FileContent(std::string filename):ContentGenerator() {
    m_filename=filename;
}
 void FileContent::handler(HTTPRequest req) {
             if(req.uri=="/"){
                 std::ifstream infile {m_filename };
                 std::string file_contents { std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>() };

                 Ok(req,file_contents);
             }else {
                 NotFound(req);
             }

}