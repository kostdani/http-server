//
// Created by kostdani on 6/13/21.
//

#ifndef SERVER_CONTENTGENERATOR_H
#define SERVER_CONTENTGENERATOR_H
#include "HTTPRequest.h"
#include "Queuer.h"
class ContentGenerator: public Queuer<HTTPRequest>{
public:
    ContentGenerator()=default;

protected:
    void NotFound(HTTPRequest req) const;

    void Forbidden(HTTPRequest req) const;

    void Ok(HTTPRequest req,std::string body) const;

    void NotImplemented(HTTPRequest req) const;
};


#endif //SERVER_CONTENTGENERATOR_H
