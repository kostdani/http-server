#include "tcpserver.hpp"

TCPServer::TCPServer(int descriptor):Socket(PF_INET,SOCK_STREAM,0,descriptor){}

void TCPServer::Close()
{
    shutdown(m_descriptor, SHUT_RDWR);
    Socket::Close();
}


bool TCPServer::Bind(const char *address, int port){
    if (inet_pton(AF_INET, address, &m_address.sin_addr) <= 0)
    {
        printf("error: cant convert address\n");
        return false;
    }
    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(port);

    return bind(m_descriptor,(sockaddr*)&m_address,sizeof(m_address))==0;
}


bool TCPServer::Listen(int backlog){
    return listen(m_descriptor,backlog)==0;
}

TCPSocket TCPServer::Accept(){
    sockaddr_in cli_addr;
    socklen_t ca_len=0;
    int desc=accept(m_descriptor,(sockaddr *)&cli_addr,&ca_len);
    return TCPSocket(desc,cli_addr);
}
