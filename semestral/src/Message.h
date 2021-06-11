//
// Created by kostdani on 5/31/21.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H
#include <string>

struct Message {
    enum class msg_type
    {
        ERROR,
        SETTINGS,
        BYTEARRAY
    };
    msg_type type;
    std::string msg;
};


#endif //SERVER_MESSAGE_H
