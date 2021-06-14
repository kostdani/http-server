//
// Created by kostdani on 6/14/21.
//

#include "ScriptContent.h"

ScriptContent::ScriptContent(std::string scriptname) {
    m_scriptname=scriptname;
}

void ScriptContent::handler(HTTPRequest msg) {
    FILE  *fp;
    fp=popen("./script.sh","r");

}