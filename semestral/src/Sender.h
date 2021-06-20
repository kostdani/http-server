//
// Created by kostdani on 6/8/21.
//

#ifndef SERVER_SENDER_H
#define SERVER_SENDER_H
#include "Queuer.h"

/// Sender actor
///
/// Sends data to client
class Sender: public Queuer<std::string>{
public:
    /// @param descriptor tcp socket of client
    Sender(int descriptor);

    void Run(int threadi) override;

    void Error(int threadi) override;
    /// Sends msg to client if possible
    void handler(std::string& msg) override;
    /// Tracks input events on queue and output events on socket, level triggered

    bool multiplex(int epollfd) override;
protected:
    uint32_t TrackedEvents() const override;
    int m_socketfd=-1;
    std::string last;
    ssize_t n=0;

};


#endif //SERVER_SENDER_H
