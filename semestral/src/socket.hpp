#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

class Socket
{
public:
    //constructor
    Socket(int domain,int type, int protocol=0,int descriptor =-1);

    bool Check();
    virtual void Close();
        
    
protected:
    int m_descriptor;
    sockaddr_in m_address;
    bool m_closed;
        
};
