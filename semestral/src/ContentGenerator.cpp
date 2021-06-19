//
// Created by kostdani on 6/13/21.
//

#include "ContentGenerator.h"

void ContentGenerator::NotFound(HTTPRequest& req)  const{
    req.SetCode(Status_Code::Not_Found);
    //req.SetBody("<h1>Error: "+Status_Code::Not_Found+"</h1>");
    req.Finish();
}

void ContentGenerator::Forbidden(HTTPRequest& req)  const{
    req.SetCode(Status_Code::Forbidden);
    //req.SetBody("<h1>Error: "+Status_Code::Forbidden+"</h1>");
    req.Finish();
}

void ContentGenerator::NotImplemented(HTTPRequest& req)  const{
    req.SetCode(Status_Code::Not_Impelemented);
    //req.SetBody("<h1>Error: "+Status_Code::Not_Impelemented+"</h1>");
    req.Finish();
}

void ContentGenerator::Ok(HTTPRequest& req,const std::string& body)  const{
    req.SetCode(Status_Code::OK);
    req.SetBody(body);
    req.Finish();
}