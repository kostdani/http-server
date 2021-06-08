//
// Created by kostdani on 5/22/21.
//

#ifndef SERVER_EPOLLER_H
#define SERVER_EPOLLER_H
#include "Actor.h"
#include <set>
class Epoller : public Actor{
public:
    Epoller();

    ~Epoller();

    epoll_event getEvent();

    bool AddActor(Actor * newActor) override;

protected:
    std::set<Actor *> m_actors;
};


#endif //SERVER_EPOLLER_H