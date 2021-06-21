//
// Created by kostdani on 6/14/21.
//

#include "TerminatorContent.h"

TerminatorContent::TerminatorContent(bool &stopb):m_stop(stopb) {}

void TerminatorContent::Run(uint32_t events) {
        m_stop=true;
}

void TerminatorContent::handler(HTTPRequest &msg) {}

uint32_t TerminatorContent::TrackedEvents() const {
    return EPOLLIN;
}