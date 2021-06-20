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

/// Virtual class parent of all actors
///
/// Actor is an object getting events which can be tracked by epoll
/// technically it's a wrapper for unix descriptor
class Actor {
public:
    /// Constructor
    /// @param descriptor Descriptor to be wrapped
    Actor(int descriptor);
    /// Destructor
    /// Closes descriptor and frees memory if needed
    virtual ~Actor();

    /// Function that closes descriptor
    void Close();

    /// Checks if decriptor is ok
    bool Check() const;

    Actor(const Actor&) =delete;
    Actor& operator=(const Actor&)=delete;

    /// Add new actor
    /// Puts the actor to be listened by same epoll as this
    /// @param newActor Actor to be added
    virtual bool AddActor(Actor * actor);

    virtual bool RmActor(Actor * actor);

    /// A method that implements the behavior of an actor on input event
    virtual void Run(int threadi)=0;

    /// A method that implements the behavior of an actor on output event
    virtual void Error(int threadi)=0;

    friend class Epoller;

    /// Multiplexes actor on epoll
    /// Tracks input and output events level triggered
    /// @param epolld epoll file descriptor
    /// @returns true if multiplexd sucessfuly othewise false
    virtual bool multiplex(int epolld);
protected:
    virtual uint32_t TrackedEvents() const=0;
    Actor *m_parent= nullptr;
    int m_descriptor=-1;
};


#endif //SERVER_ACTOR_H
