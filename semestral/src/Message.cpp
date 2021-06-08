//
// Created by kostdani on 5/31/21.
//

#include "Message.h"

ClientSettings::ClientSettings(int d) {
    m_descriptor=d;
}

TextMsg::TextMsg(std::string str) {
    m_str=str;
}