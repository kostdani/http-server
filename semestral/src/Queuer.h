//
// Created by kostdani on 5/31/21.
//

#ifndef SERVER_QUEUER_H
#define SERVER_QUEUER_H
#include "Counter.h"
#include <queue>
#include <mutex>
/// Queue actor manage queue of messages and react on them
template <class T>
class Queuer : public Counter {
public:
    Queuer();

    /// Pushes new message to queue
    void Push(const T& msg);
    /// Gets last message from queue if there
    std::pair<T,bool> Pop();

    void Run(uint32_t events) override;

    /// Virtual function to implement reaction on messages
    virtual void handler(T& msg)=0;

    uint32_t TrackedEvents() const override;
protected:
    using Counter::Add;
    using Counter::Reset;
    std::queue<T> m_queue;
    std::mutex m_mtx;
};

#include "Queuer.ipp"

#endif //SERVER_QUEUER_H
