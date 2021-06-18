//
// Created by kostdani on 6/13/21.
//

#include "ContentGenerator.h"

void ContentGenerator::NotFound(HTTPRequest& req)  const{
    req.SetCode("404 Not Found");
    req.SetBody("<div id=\"main\">\n"
                     "    \t<div class=\"fof\">\n"
                     "        \t\t<h1>Error 404</h1>\n"
                     "    \t</div>\n"
                     "</div>");
    req.Finish();
}

void ContentGenerator::Forbidden(HTTPRequest& req)  const{
    req.SetCode("403 Forbidden");
    req.SetBody("<div id=\"main\">\n"
                     "    \t<div class=\"fof\">\n"
                     "        \t\t<h1>Error 403</h1>\n"
                     "    \t</div>\n"
                     "</div>");
    req.Finish();
}

void ContentGenerator::NotImplemented(HTTPRequest& req)  const{
    req.SetCode("501 Not Implemented");
    req.SetBody("<div id=\"main\">\n"
                     "    \t<div class=\"fof\">\n"
                     "        \t\t<h1>Error 501</h1>\n"
                     "    \t</div>\n"
                     "</div>");
    req.Finish();
}

void ContentGenerator::Ok(HTTPRequest& req,const std::string& body)  const{
    req.SetCode("200 OK");
    req.SetBody(body);
    req.Finish();
}