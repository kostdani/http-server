#include <iostream>
#include "Epoller.h"
#include "Accepter.h"
#include "Counter.h"
#include "Timer.h"
#include "Sender.h"
#include "Logger.h"
#include <thread>
#include "FileContent.h"
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
std::string sample("GET / HTTP/1.0\n"
                    "Host: 127.0.0.1:8080\n\n");


int main() {
    HTTPRequest req(sample);



    //auto l =new Logger("server.log");
    //auto ac=new Accepter(l,"127.0.0.1",8080);
    auto f= new FileContent("/home/kostdani/index.html");
    Epoller epoll;
    epoll.AddActor(f);
    //epoll.AddActor(ac);
    //epoll.AddActor(l);
    auto cnt=new Counter();
    epoll.AddActor(cnt);
    std::thread thr(thrfunc,&epoll);

    std::cout << "waiting for my lord" << std::endl;
    std::cin.ignore();

    f->Push(req);

    stop=true;
    cnt->Add(1);
    thr.join();
    return 0;
}
