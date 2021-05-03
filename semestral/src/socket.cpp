#include "socket.hpp"


Socket::Socket(int domain,int type, int protocol,int descriptor ){
    m_closed=false;
    if(!Check())
        m_descriptor=socket(domain,type,protocol);
    else
        m_descriptor=descriptor;
    if(!Check()){
        printf("cant create socket");
    //    exit(1);
    }
        
}

bool Socket::Check(){
    return m_descriptor>=0;
}

void Socket::Close(){
    if(!m_closed){
        m_closed=true;
        close(m_descriptor);
    }
}
