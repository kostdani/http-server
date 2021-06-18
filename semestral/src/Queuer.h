//
// Created by kostdani on 5/31/21.
//

#ifndef SERVER_QUEUER_H
#define SERVER_QUEUER_H
#include "Counter.h"
#include <queue>
#include <mutex>
/// Queue actor
///
/// Actor used to manage queue of messages and react on them
template <class T>
class Queuer : public Counter {
public:
    Queuer();

    /// Pushes new message to queue
    void Push(const T& msg);
    /// Gets last message from queue if there
    std::pair<T,bool> Pop();

    void Run(int threadi) override;

    void Error(int threadi) override;
    /// Virtual function to implement reaction on messages
    virtual void handler(T& msg)=0;

    bool multiplex(int epolld) override;
protected:
    std::queue<T> m_queue;
    std::mutex m_mtx;
};

#include "Queuer.ipp"

#endif //SERVER_QUEUER_H
