//
// Created by kostdani on 5/22/21.
//

#ifndef SERVER_EPOLLER_H
#define SERVER_EPOLLER_H
#include "Actor.h"
#include <set>

/// Epoll actor, wrapper for epoll file descriptor
class Epoller : public Actor{
public:
    Epoller();

    ~Epoller();

    /// Get next event
    /// @returns Next event, blocking the calling thread if no events are currently available.
    epoll_event GetEvent();

    /// Registers given actor to be listened by epoll
    /// @note Cares about memory management i.e. class will free all actors in destructor
    /// @param actor Actor to be added
    bool AddActor(Actor * actor) override;

    /// Remove given actor from listened by epoll
    /// @param actor Actor to be removed
    bool RmActor(Actor * actor);

    void Run(uint32_t events) override;

protected:
    uint32_t TrackedEvents() const override;
    std::set<Actor *> m_actors;
};


#endif //SERVER_EPOLLER_H
