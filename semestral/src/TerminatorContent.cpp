//
// Created by kostdani on 6/14/21.
//

#include "TerminatorContent.h"

TerminatorContent::TerminatorContent(bool &stopb, std::vector<std::thread> &thrvec):m_stop(stopb),m_threads(thrvec) {

}

void TerminatorContent::Run(int threadi) {
    if(threadi==0){
        m_stop=true;
        for (auto & thr:m_threads)
            thr.join();

    }

}

bool TerminatorContent::multiplex(int epolld) {
    return Counter::multiplex(epolld);
}