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

void ContentGenerator::Forbidden(HTTPRequest req) {
    req.respond.code="403 Forbidden";
    req.m_log.status="403";
    req.respond.body="<div id=\"main\">\n"
                     "    \t<div class=\"fof\">\n"
                     "        \t\t<h1>Error 403</h1>\n"
                     "    \t</div>\n"
                     "</div>";
    req.respond.headers["Content-Length"]=std::to_string(req.respond.body.length());
    req.m_log.bytes=std::to_string(req.respond.body.length());
    req.Finish();
}

void ContentGenerator::NotImplemented(HTTPRequest req) {
    req.respond.code="501 Not Implemented";
    req.m_log.status="501";
    req.respond.body="<div id=\"main\">\n"
                     "    \t<div class=\"fof\">\n"
                     "        \t\t<h1>Error 501</h1>\n"
                     "    \t</div>\n"
                     "</div>";
    req.respond.headers["Content-Length"]=std::to_string(req.respond.body.length());
    req.m_log.bytes=std::to_string(req.respond.body.length());
    req.Finish();
}

void ContentGenerator::Ok(HTTPRequest req,std::string body) {
    req.respond.code="200 OK";
    req.m_log.status="200";
    req.respond.body=body;
    req.respond.headers["Content-Length"]=std::to_string(req.respond.body.length());
    req.m_log.bytes=std::to_string(req.respond.body.length());
    req.Finish();
}