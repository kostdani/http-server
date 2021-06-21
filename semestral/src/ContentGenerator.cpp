//
// Created by kostdani on 6/13/21.
//

#include "ContentGenerator.h"

void ContentGenerator::NotFound(HTTPRequest& req)  const{
    req.SetCode(Status_Code::Not_Found);
    req.Finish();
}

void ContentGenerator::Forbidden(HTTPRequest& req)  const{
    req.SetCode(Status_Code::Forbidden);
    req.Finish();
}

void ContentGenerator::NotImplemented(HTTPRequest& req)  const{
    req.SetCode(Status_Code::Not_Impelemented);
    req.Finish();
}

void ContentGenerator::Ok(HTTPRequest& req,const std::string& body)  const{
    req.SetCode(Status_Code::OK);
    req.SetBody(body);
    req.Finish();
}
void ContentGenerator::InternalError(HTTPRequest &req) const {
    req.SetCode(Status_Code::Internal_Error);
    req.Finish();
}