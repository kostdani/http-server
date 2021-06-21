//
// Created by kostdani on 6/8/21.
//

#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H
#include "Queuer.h"
#include <atomic>
/// Sender actor, sends data to client
class Sender: public Queuer<std::string>{
public:
    /// @param descriptor tcp socket of client
    Sender(int descriptor);

    void Run(uint32_t events) override;
    /// Sends msg to client if possible
    void handler(std::string& msg) override;

    std::atomic<int> awaitedmsgs;
protected:
    /// Multiplexes bot queuer and tcp client socket
    bool multiplex(int epollfd) override;

    uint32_t TrackedEvents() const override;
    int m_socketfd=-1;
    std::string last;
    ssize_t n=0;
    bool m_finishing= false;
};


#endif //SERVER_SENDER_H
