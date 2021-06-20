//
// Created by kostdani on 6/14/21.
//

#include "TerminatorContent.h"

TerminatorContent::TerminatorContent(bool &stopb, std::vector<std::thread> &thrvec):m_stop(stopb),m_threads(thrvec) {

}

void TerminatorContent::Run(uint32_t events) {
        m_stop=true;

}

uint32_t TerminatorContent::TrackedEvents() const {
    return EPOLLIN;
}