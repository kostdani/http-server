//
// Created by kostdani on 6/13/21.
//

#ifndef SERVER_CONTENTGENERATOR_H
#define SERVER_CONTENTGENERATOR_H
#include "HTTPRequest.h"
#include "Queuer.h"

/// Actor which generates responds for http requests
class ContentGenerator: public Queuer<HTTPRequest>{
public:
    ContentGenerator()=default;

protected:
    /// Responds with error 404 Not Found
    void NotFound(HTTPRequest& req) const;
    /// Responds with error 403 Forbidden
    void Forbidden(HTTPRequest& req) const;
    /// Responds with code 200 OK and given respond body
    void Ok(HTTPRequest& req,const std::string& body) const;
    /// Responds with error 501 Not Implemented
    void NotImplemented(HTTPRequest& req) const;
};


#endif //SERVER_CONTENTGENERATOR_H
