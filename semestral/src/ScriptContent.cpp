//
// Created by kostdani on 6/19/21.
//

#include "ScriptContent.h"

const int BUFSIZE=4096;

ScriptContent::ScriptContent(const std::string &filename) {
    m_filename=filename;
}

void ScriptContent::handler(HTTPRequest &msg) {

    FILE *pipe=popen((m_filename+" 2>/dev/null "+msg.GetParams()).c_str(),"r");
    char buffer[BUFSIZE];
    std::string result;
    if (!pipe){
        InternalError(msg);
        return;
    }
    while (fgets(buffer, BUFSIZE, pipe) != nullptr)
        result += buffer;
    pclose(pipe);
    Ok(msg,result);
}