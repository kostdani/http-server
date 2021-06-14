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

    void onInput(int threadi) override;


    bool multiplex(int epolld) override;
protected:
    timespec m_timeout{};
};


#endif //SERVER_TIMER_H
