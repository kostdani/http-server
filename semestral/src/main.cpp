#include <iostream>
#include "Epoller.h"
#include "Accepter.h"
#include "Counter.h"
#include "Timer.h"
#include "Sender.h"
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

class A{
public:
    A(int a){
        this->a=a;
    }
    virtual void print(){
        printf("a\n");
    }
    int a;
};
class B:public A{
public:
    B(int b):A(b){
    }
    void print() override{

        printf("b\n");
    }
};


int main() {

    Epoller epoll;
    auto ac=new Accepter("127.0.0.1",8080);
    epoll.AddActor(ac);
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
