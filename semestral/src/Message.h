//
// Created by kostdani on 5/31/21.
//

#ifndef SERVER_MESSAGE_H
#define SERVER_MESSAGE_H


class Message {
public:
    Message()=default;
};


class ClientSettings : public Message{
public:
    ClientSettings(int d);

    int m_descriptor;
};

#endif //SERVER_MESSAGE_H
