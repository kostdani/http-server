//
// Created by kostdani on 5/31/21.
//

#ifndef SERVER_QUEUER_H
#define SERVER_QUEUER_H
#include "Counter.h"
#include "Message.h"
#include <queue>
#include <mutex>
class Queuer : public Counter {
public:
    Queuer();

   // ~Queuer();

    void Put(Message * msg);

    Message * Get();

    bool Empty() const;

    void msghandler(Message *msg){
        printf("emptymsg\n");
    }
    void msghandler(TextMsg *msg){
        printf("testmsg: ");
        std::cout<<msg->m_str<<std::endl;
    }

    void onInput() override;

protected:
    bool multiplex(int epolld) override;
    std::queue<Message *> m_queue;
    std::mutex m_mtx;
};


#endif //SERVER_QUEUER_H
