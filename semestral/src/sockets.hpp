#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory>
#include <iostream>

namespace MyServer{
    class Socket
    {
    public:
        //constructor
        Socket(int descriptor);
        //destuctor
        ~Socket();

        
        //check valid
        bool Check();
        

    protected:
        int m_descriptor;
        struct sockaddr_in m_address;
        
    };

    
    class AcceptedSocket : public Socket{
    public:
       
        AcceptedSocket(int descriptor,sockaddr_in address);

        friend std::ostream & operator<<(std::ostream & os,const AcceptedSocket &sc);
        
    };
    std::ostream & operator<<(std::ostream & os,const AcceptedSocket &sc);
    

    class ServerSocket : public Socket{
    public:
        
        ServerSocket(int descriptor, sockaddr_in address, int backlog);
        
        bool Bind(sockaddr_in address);
        bool Listen(int backlog);
        std::shared_ptr<AcceptedSocket> Accept();
        
    };

       
    

    
}

