//
// Created by kostdani on 5/29/21.
//

#include "Timer.h"

Timer::Timer(uint timeout): Actor(timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK)){
    SetTimeout(timeout);
    ResetTimer();
}

void Timer::SetTimeout(uint timeout) {
    m_timeout.tv_sec=timeout;
}

void Timer::ResetTimer() {
    struct itimerspec its{};
    its.it_value=m_timeout;
    timerfd_settime(m_descriptor,0,&its,0);
}

void Timer::Run(uint32_t events) {
    printf("timerhah\n");
    ResetTimer();
}

uint32_t Timer::TrackedEvents() const {
    return EPOLLIN|EPOLLET;
}
