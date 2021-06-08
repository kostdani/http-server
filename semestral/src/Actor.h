//
// Created by kostdani on 5/22/21.
//

#ifndef SERVER_ACTOR_H
#define SERVER_ACTOR_H

#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <iostream>
class Actor {
public:
    // Constructor
    Actor(int descriptor);
    // Destructor
    virtual ~Actor();
    // No copy
    Actor(const Actor&) =delete;
    Actor& operator=(const Actor&)=delete;
    // Checks if decriptor is ok
    bool Check();

    // Create new actor
    virtual bool AddActor(Actor * newActor);

    // method to call on input event
    virtual void onInput();
    // method to call on output event
    virtual void onOutput();
    // method to call on error event
    virtual void onError();

    friend class Epoller;


protected:
    virtual bool multiplex(int epolld);
    Actor *m_parent=0;
    int m_descriptor=-1;
};


#endif //SERVER_ACTOR_H
