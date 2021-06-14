//
// Created by kostdani on 5/22/21.
//

#ifndef SERVER_ACTOR_H
#define SERVER_ACTOR_H
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <iostream>
#include <functional>

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

    void Close();
    // Create new actor
    virtual bool AddActor(Actor * newActor);

    // method to call on input event
    virtual void onInput(int threadi);
    // method to call on output event
    virtual void onOutput(int threadi);
    // method to call on error event
    virtual void onError(int threadi);

    friend class Epoller;

    virtual bool multiplex(int epolld);
protected:
    Actor *m_parent=0;
    int m_descriptor=-1;
};


#endif //SERVER_ACTOR_H
