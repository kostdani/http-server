#include "tcpsocket.hpp"




TCPSocket::TCPSocket(int descriptor,sockaddr_in address):Socket(PF_INET,SOCK_STREAM,0,descriptor){
    m_address=address;
}

bool TCPSocket::Send(const char *str, size_t str_len)
{
    return !(m_closed || send(this->m_descriptor, str, str_len, 0) < 0);
}

bool TCPSocket::Send(std::string str)
{
    return this->Send(str.c_str(), str.length());
}

int TCPSocket::Recieve (char *buf, size_t buf_len){
    return recv(m_descriptor,buf,buf_len,0);
}
std::string TCPSocket::Recieve (){
    std::string res;
    char buf[256];
    int l=0;
    while((l=Recieve(buf,256))>0){
        printf("recieved %d bytes\n",(int)l);
        res.append(buf,buf+l);
        if(l!=256)
            break;
    }
    
        printf("recieved total of  %d bytes\n",(int)res.size());
    return res;
}
