//
// Created by kostdani on 5/31/21.
//

#ifndef SERVER_QUEUER_H
#define SERVER_QUEUER_H
#include "Counter.h"
#include <queue>
/// Queue actor manage queue of messages and react on them
template <class T>
class Queuer : public Counter {
public:
    Queuer();
    /// Pushes new message to queue
    void Push(const T& msg);
    /// Gets last message from queue if there
    // @returns pair where second elem is bool representing if the value actualy presents
    std::pair<T,bool> Pop();
    /// Virtual function to implement reaction on messages
    virtual void handler(T& msg)=0;

    void Run(uint32_t events) override;
protected:
    using Counter::Add;
    using Counter::Reset;
    /// Tracks input events edge-triggered
    uint32_t TrackedEvents() const override;
    /// Queue of messages
    std::queue<T> m_queue;
};

#include "Queuer.ipp"

#endif //SERVER_QUEUER_H
