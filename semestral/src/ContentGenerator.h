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

    void NotFound(HTTPRequest req);

    void Forbidden(HTTPRequest req);
protected:
};


#endif //SERVER_CONTENTGENERATOR_H
