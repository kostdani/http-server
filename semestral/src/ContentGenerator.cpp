//
// Created by kostdani on 6/13/21.
//

#include "ContentGenerator.h"

void ContentGenerator::NotFound(HTTPRequest req) {
    req.respond.code="404 Not Found";
    req.m_log.status="404";
    req.respond.body="<div id=\"main\">\n"
                     "    \t<div class=\"fof\">\n"
                     "        \t\t<h1>Error 404</h1>\n"
                     "    \t</div>\n"
                     "</div>";
    req.respond.headers["Content-Length"]=std::to_string(req.respond.body.length());
    req.m_log.bytes=std::to_string(req.respond.body.length());
    req.Finish();
}