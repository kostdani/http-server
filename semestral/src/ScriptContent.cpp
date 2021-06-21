//
// Created by kostdani on 6/19/21.
//

#include "ScriptContent.h"

const int BUFSIZE=4096;

ScriptContent::ScriptContent(const std::string &filename) {
    m_filename=filename;
}

void ScriptContent::handler(HTTPRequest &req) {
    if(req.GetMethod()!="GET"){
        NotImplemented(req);
        return;
    }

    struct stat buf{};
    if(req.GetURI()=="/" && stat(m_filename.c_str(),&buf)==0){
        FILE *pipe=popen((m_filename+" 2>/dev/null "+req.GetParams()).c_str(),"r");
        char buffer[BUFSIZE];
        std::string result;
        if (!pipe){
            InternalError(req);
            return;
        }
        while (fgets(buffer, BUFSIZE, pipe) != nullptr)
            result += buffer;
        pclose(pipe);
        Ok(req,result);
    }else {
        NotFound(req);
    }


}