//
// Created by kostdani on 6/14/21.
//

#include "TerminatorContent.h"

TerminatorContent::TerminatorContent(bool &stopb, std::vector<std::thread> &thrvec):m_stop(stopb),m_threads(thrvec) {

}

void TerminatorContent::onInput(int threadi) {
    if(threadi==0){
        m_stop=true;
        for (auto & thr:m_threads)
            thr.join();
    }

}