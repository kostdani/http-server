#include "sockets.hpp"


MyServer::Socket::Socket(int descriptor){
    m_descriptor=descriptor;
}

bool MyServer::Socket::Check(){
    return m_descriptor!=-1;
}

MyServer::Socket::~Socket(){
    if(Check())
        close(m_descriptor);
}

MyServer::AcceptedSocket::AcceptedSocket(int descriptor,sockaddr_in address): Socket(descriptor){
    m_address=address;
}


bool MyServer::ServerSocket::Bind(sockaddr_in address){
    return bind(m_descriptor,(sockaddr*)&address,sizeof(address))==0;
}


bool MyServer::ServerSocket::Listen(int backlog){
    return listen(m_descriptor,backlog)==0;
}


MyServer::ServerSocket::ServerSocket(int descriptor, sockaddr_in address, int backlog): Socket(descriptor){
    m_address=address;
    
    if(!Bind(address) || !Listen(backlog)){
        printf("error\n");
        exit(1);
    }
    
}


std::shared_ptr<MyServer::AcceptedSocket> MyServer::ServerSocket::Accept(){
    struct sockaddr_in a;
    socklen_t al;
    int b=accept(m_descriptor,(struct sockaddr *)&a,&al);
    return std::make_shared<MyServer::AcceptedSocket>(b,a);
}

std::ostream & MyServer::operator<<(std::ostream & os,const AcceptedSocket& sc){
    char buf[264];
    int n=0;
    while((n=read(sc.m_descriptor , buf, 264))){
        os.write(buf, n);
    }
    return os;
}
