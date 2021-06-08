#include <iostream>
#include "Epoller.h"
#include "Accepter.h"
#include "Counter.h"
#include "Timer.h"
#include <thread>
bool stop=false;

void thrfunc(Epoller *epoll){
    while (!stop){

        auto ev=epoll->getEvent();
        Actor *actor=(Actor *)ev.data.ptr;
        if((ev.events&EPOLLERR)||(ev.events&EPOLLHUP)||(ev.events&EPOLLRDHUP)){
            actor->onError();
        }else{
            if(ev.events&EPOLLIN)
                actor->onInput();
            if(ev.events&EPOLLOUT)
                actor->onOutput();

        }
    }
}

int main() {
    Epoller epoll;
    auto ac=new Accepter("127.0.0.1",8080);
    auto t=new Timer(1);
    t->ResetTimer();
    epoll.AddActor(ac);
    epoll.AddActor(t);
    auto cnt=new Counter();
    epoll.AddActor(cnt);
    std::thread thr(thrfunc,&epoll);

    std::cout << "waiting for my lord" << std::endl;
    std::cin.ignore();
    stop=true;
    cnt->Add(1);
    thr.join();
    return 0;
}
