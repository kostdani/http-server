//
// Created by kostdani on 5/28/21.
//

#ifndef SERVER_COUNTER_H
#define SERVER_COUNTER_H
#include "Actor.h"
#include <sys/eventfd.h>

/// Counter actor
///
/// Class wrapper for eeventfd
class Counter: public Actor {
public:
    Counter();

    /// Add x to eventfd counter
    void Add(eventfd_t x);

    /// Set eventfd to 0
    void Reset();

    /// Tracks input events level triggered
    bool multiplex(int epolld) override;
protected:
};


#endif //SERVER_COUNTER_H
