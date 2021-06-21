//
// Created by kostdani on 5/22/21.
//

#ifndef SERVER_EPOLLER_H
#define SERVER_EPOLLER_H
#include "Actor.h"
#include <set>
#include <mutex>

/// Epoll actor, wrapper for epoll file descriptor
class Epoller : public Actor{
public:
    Epoller();

    ~Epoller();

    /// Get next event
    /// @returns Next event, blocking the calling thread if no events are currently available.
    epoll_event GetEvent();

    /// Add new actor
    /// Registers given actor to be listened by epoll
    /// @note Cares about memory management i.e. class will free all actors in destructor
    /// @param newActor Actor to be added
    bool AddActor(Actor * actor) override;

    bool RmActor(Actor * actor) override;

    void Run(uint32_t events) override;

protected:
    uint32_t TrackedEvents() const override;
    std::set<Actor *> m_actors;
    std::mutex m_mtx;
};


#endif //SERVER_EPOLLER_H
