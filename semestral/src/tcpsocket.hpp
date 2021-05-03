#include "socket.hpp"
#include <string>

class TCPSocket : public Socket
{
public:
    //TCPSocket(int descriptor =-1);
    TCPSocket(int descriptor =-1,sockaddr_in address={});

    bool Send(const char *str,size_t str_len);
    bool Send(std::string str);
    int Recieve (char *buf, size_t buf_len);
    std::string Recieve ();
    
};
