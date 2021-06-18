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

void Timer::Run(int threadi) {
    printf("timerhah\n");
    ResetTimer();
}

void Timer::Error(int threadi) {

}

bool Timer::multiplex(int epolld) {

    epoll_event ev{};
    ev.data.ptr = this;
    ev.events = EPOLLIN | EPOLLET;

    return epoll_ctl(epolld, EPOLL_CTL_ADD, m_descriptor, &ev) == 0;

}