//
// Created by kostdani on 5/31/21.
//

#ifndef SERVER_QUEUER_H
#define SERVER_QUEUER_H
#include "Counter.h"
#include <queue>
#include <mutex>

template <class T>
class Queuer : public Counter {
public:
    Queuer();
   // ~Queuer();

    void Push(T msg);

    std::pair<T,bool> Pop();

    bool Empty() const;

    void onInput(int threadi) override;

    virtual void handler(T msg);

    bool multiplex(int epolld) override;
protected:
    std::queue<T> m_queue;
    std::mutex m_mtx;
};

#include "Queuer.ipp"

#endif //SERVER_QUEUER_H
