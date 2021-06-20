//
// Created by kostdani on 5/29/21.
//

#ifndef SERVER_TIMER_H
#define SERVER_TIMER_H
#include "Actor.h"
#include <sys/timerfd.h>

// Wrapper for timerfd
class Timer:public Actor{
public:
    // Constructor with timeout
    Timer(uint timeout=0);
    // Sets Timeout
    void SetTimeout(uint timeout);
    // Resets timer
    void ResetTimer();


    void Run(int threadi) override;

    void Error(int threadi) override;

protected:
    uint32_t TrackedEvents() const override;
    timespec m_timeout{};
};


#endif //SERVER_TIMER_H
