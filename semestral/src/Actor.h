//
// Created by kostdani on 5/22/21.
//

#ifndef SERVER_ACTOR_H
#define SERVER_ACTOR_H
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <iostream>
#include <exception>

/// Virtual class parent of all actors, an object getting events which can be tracked by epoll
class Actor {
public:
    /// Constructor
    /// @param descriptor Descriptor to be wrapped
    Actor(int descriptor);
    /// Destructor
    /// Closes descriptor and frees memory if needed
    virtual ~Actor();
    /// Closes descriptor
    void Close();
    /// Checks if decriptor is ok
    bool Check() const;
    Actor(const Actor&) =delete;
    Actor& operator=(const Actor&)=delete;
    /// Add new actor
    /// Puts the actor to be listened by same epoll as this
    /// @param newActor Actor to be added
    virtual bool AddActor(Actor * actor);
    /// A method that implements the behavior of an actor on input event
    /// @param events flag specifying which event happened
    virtual void Run(uint32_t events)=0;

    friend class Epoller;
protected:
    /// Multiplexes actor on epoll
    /// @param epolld epoll file descriptor
    /// @returns true if multiplexed sucessfuly othewise false
    virtual bool multiplex(int epolld);
    /// Returns flags specifying how should epoll track this actor
    virtual uint32_t TrackedEvents() const=0;
    /// Points to epoll which is tacking this actor
    Actor *m_parent= nullptr;
    /// Actors's main descriptor
    int m_descriptor=-1;
};


#endif //SERVER_ACTOR_H
