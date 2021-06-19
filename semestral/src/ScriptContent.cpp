//
// Created by kostdani on 6/19/21.
//

#include "ScriptContent.h"

ScriptContent::ScriptContent(const std::string &filename) {
    m_filename=filename;
}

void ScriptContent::handler(HTTPRequest &msg) {

    FILE *pipe=popen((m_filename+" "+msg.GetParams()).c_str(),"r");
    char buffer[128];
    std::string result;
    if (!pipe){
        NotImplemented(msg);
        return;
    }
    while (fgets(buffer, 128, pipe) != NULL) {
        result += buffer;
    }
    pclose(pipe);

    Ok(msg,result);
}