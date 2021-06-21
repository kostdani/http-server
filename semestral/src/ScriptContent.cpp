//
// Created by kostdani on 6/19/21.
//

#include "ScriptContent.h"

ScriptContent::ScriptContent(const std::string &filename) {
    m_filename=filename;
}

void ScriptContent::handler(HTTPRequest &msg) {

    FILE *pipe=popen((m_filename+" 2>/dev/null "+msg.GetParams()).c_str(),"r");
    char buffer[4096];
    std::string result;
    if (!pipe){
        NotImplemented(msg);
        return;
    }
    while (fgets(buffer, 4096, pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);

    Ok(msg,result);
}