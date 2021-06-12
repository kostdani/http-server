#include <iostream>
#include "Epoller.h"
#include "Accepter.h"
#include "Counter.h"
#include "Timer.h"
#include "Sender.h"
#include "Logger.h"
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
auto l =new Logger("server.log");


    Epoller epoll;
    auto ac=new Accepter("127.0.0.1",8080);
    //epoll.AddActor(ac);
    epoll.AddActor(l);
    auto cnt=new Counter();
    epoll.AddActor(cnt);
    std::thread thr(thrfunc,&epoll);
    l->Push("TESTMSG\n");
    l->Push("SecondMSG\n");

    std::cout << "waiting for my lord" << std::endl;
    std::cin.ignore();


    stop=true;
    cnt->Add(1);
    thr.join();
    return 0;
}
