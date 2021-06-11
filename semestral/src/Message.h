//
// Created by kostdani on 5/31/21.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H
#include <string>

struct Message {

    Message()=default;
};


class ClientSettings : public Message{
public:
    ClientSettings(int d);

    int m_descriptor;
};

class TextMsg: public Message{
public:
    TextMsg(std::string str);
    std::string m_str;
};

#endif //SERVER_MESSAGE_H
