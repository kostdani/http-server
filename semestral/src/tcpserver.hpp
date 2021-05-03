#include "tcpsocket.hpp"

class TCPServer : public Socket
{
    public:
    TCPServer(int descriptor =-1);
    void Close();
    bool Bind(const char *address="0.0.0.0", int port=80);
    bool Listen(int backlog=100);
    TCPSocket Accept();
    
};
