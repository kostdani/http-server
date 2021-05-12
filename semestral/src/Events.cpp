#include "Events.h"
#include <iostream>
using namespace Events;
const int EPOLL_SIZE=666;
// BaseEvent
BaseEvent::BaseEvent(int d):m_descriptor(d) {}
bool BaseEvent::Check() const {return m_descriptor!=-1;}
void BaseEvent::Close() {
    if(Check())
        close(m_descriptor);
    m_descriptor=-1;
}
bool BaseEvent::Multiplex(int epolldf) {
    struct epoll_event ev{};
    ev.data.ptr=this;
    ev.events = EPOLLIN | EPOLLERR | EPOLLET;
    int i=epoll_ctl(epolldf, EPOLL_CTL_ADD, m_descriptor, &ev);
}
int BaseEvent::Execute() {
    printf("shouldnt happen\n");
    return 0;
}


// Counter

Counter::Counter(): BaseEvent(eventfd(0,EFD_NONBLOCK)) {}

void Counter::Inc() {
    if(Check())
        eventfd_write(m_descriptor, 1);
}

void Counter::Reset() {
    if(Check()) {
        eventfd_t val;
        eventfd_read(m_descriptor, &val);
    }
}

int Counter::Execute() {
    printf("exec counter\n");
    return 0;
}

bool Counter::Multiplex(int epolldf) {
    struct epoll_event ev{};
    ev.data.ptr=this;
    ev.events = EPOLLIN | EPOLLERR;
    int i=epoll_ctl(epolldf, EPOLL_CTL_ADD, m_descriptor, &ev);
}


// Timer

Timer::Timer(timespec timeout): BaseEvent(timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK)), m_timeout(timeout) {
    ResetTimer();
}

void Timer::SetTimeout(timespec timeout) {
    m_timeout=timeout;
}

void Timer::ResetTimer() {
    struct itimerspec its{};
    its.it_value=m_timeout;
    timerfd_settime(m_descriptor,0,&its,0);
}

int Timer::Execute() {
    printf("exec timer\n");
    return 0;
}


bool Timer::Multiplex(int epolldf) {
    struct epoll_event ev{};
    ev.data.ptr=this;
    ev.events = EPOLLIN | EPOLLERR | EPOLLET;
    int i=epoll_ctl(epolldf, EPOLL_CTL_ADD, m_descriptor, &ev);
}

//IOEvent
IOEvent::IOEvent(int descriptor): BaseEvent(descriptor) {}

bool IOEvent::Ready() const {return m_ready;}

// InputEvent

InEvent::InEvent(int descriptor): IOEvent(descriptor) {}

bool InEvent::Multiplex(int epolldf) {
    struct epoll_event ev{};
    ev.data.ptr=this;
    ev.events = EPOLLIN | EPOLLET;
    int i=epoll_ctl(epolldf, EPOLL_CTL_ADD, m_descriptor, &ev);
}
int InEvent::Execute() {
    printf("exec input\n");
    m_ready=true;
    return 0;
}
// OutputEvent

OutEvent::OutEvent(int descriptor): IOEvent(descriptor) {}

bool OutEvent::Multiplex(int epolldf) {
    struct epoll_event ev{};
    ev.data.ptr=this;
    ev.events = EPOLLOUT | EPOLLET;
    int i=epoll_ctl(epolldf, EPOLL_CTL_ADD, m_descriptor, &ev);
}
int OutEvent::Execute() {
    printf("exec output\n");
    m_ready=true;
    return 0;
}

// Pumper Event

Pumper::Pumper(int in, int out):Epoller(), m_in(in), m_out(out) {
    if(!m_in.Check()||!m_in.Check())
        Close();
    else{
        m_in.Multiplex(m_descriptor);
        m_out.Multiplex(m_descriptor);
    }
}

int Pumper::Execute() {
    printf("pump event\n");
    return 0;
}

//Epoller

Epoller::Epoller(): BaseEvent(epoll_create(EPOLL_SIZE)) {}

int Epoller::Execute() {
    printf("epoll event\n");
    return 0;
}

// Dynamic Epoller

DynamicEpoller::DynamicEpoller():Epoller() {}

void DynamicEpoller::Add(std::shared_ptr<BaseEvent> event) {
    if(Check()&&event->Check()) {
        m_event.push_back(event);
        event->Multiplex(m_descriptor);
    }
}

int DynamicEpoller::Execute() {
    printf("epoll event\n");
    return 0;
}


// Accepter
sockaddr_in IPv4_converter(const char * ip,int port){
    sockaddr_in res;
    if (inet_pton(AF_INET, ip, &res.sin_addr) <= 0)
    {
        printf("error: cant convert address\n");
        exit(0);
    }
    res.sin_family = AF_INET;
    res.sin_port = htons(port);
    return res;
}


Accepter::Accepter(sockaddr_in addr): BaseEvent(socket(PF_INET, SOCK_STREAM, 0)) {

    int status = fcntl(m_descriptor, F_SETFL, fcntl(m_descriptor, F_GETFL, 0) | O_NONBLOCK);
    if (status == -1){
        printf("cant make sock non blocking\n");
        exit(1);
    }

    if(!Check()){
        printf("cant create server socket\n");
        exit(1);
    }

    if(bind(m_descriptor,(sockaddr*)&addr,sizeof(addr))==-1) {
        printf("cant bind\n");
        exit(1);
    }

    if(listen(m_descriptor,10)==-1) {
        printf("cant listen\n");
        exit(1);
    }
}

Accepter::Accepter(const char *ip, int port) : Accepter(IPv4_converter(ip,port)){};

int Accepter::Execute() {
    printf("accepter exec\n");
    return 0;
}

// Clienter

Clienter::Clienter(int decriptor, sockaddr_in addr):Epoller() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    reader=Pumper(decriptor,pipefd[1]);
    int tmp=pipefd[0];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    handler=Pumper(tmp,pipefd[1]);
    writer=Pumper(pipefd[0],dup(decriptor));

    reader.Multiplex(m_descriptor);
    writer.Multiplex(m_descriptor);
    handler.Multiplex(m_descriptor);
    timer.Multiplex(m_descriptor);
    timer.SetTimeout({1,0});
    timer.ResetTimer();
}