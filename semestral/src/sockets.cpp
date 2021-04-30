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

/*
myserver::Socket::Socket(int domain,int service,int protocol, int port, u_long interface){
    // define address sctructure
    m_address.sin_family=domain;
    m_address.sin_port=htons(port);
    m_address.sin_addr.s_addr=htonl(interface);
    // create and test socket
    m_sock=socket(domain,service,protocol);
    test_connection(m_sock);
    // set and test connection 
    m_connection=bind(m_sock,(struct sockaddr *)&m_address,sizeof(m_address));
    test_connection(m_connection);
    // set and check listening
    m_listening=listen(m_sock,10);//temporary
    test_connection(m_listening);
    
}

void myserver::Socket::test_connection(int interface){
    if(interface<0)
     {
         perror("Fail");
         exit(EXIT_FAILURE);
     }
}

// getters and setters
struct sockaddr_in myserver::Socket::Address(){
    return m_address;
}
int myserver::Socket::Connection(){
    return m_connection;
}
int myserver::Socket::Sock(){
    return m_sock;
}

void myserver::Socket::Address(struct sockaddr_in n_address){
    m_address=n_address;
}
void myserver::Socket::Connection(int n_connection){
    m_connection=n_connection;
}
void myserver::Socket::Sock(int n_sock){
    m_sock=n_sock;
}

int myserver::Socket::set_connection(int sock, struct sockaddr_in address){
    ///connectbind(int __fd, const struct sockaddr *__addr, socklen_t __len)
    //return connect(sock,(struct sockaddr *)&address,sizeof(address))
    return bind(sock,(struct sockaddr *)&address,sizeof(address));
}
using namespace std;
int main(){
    cout<<"starting"<<endl;
    myserver::Socket nsocket(AF_INET,SOCK_STREAM,0,81,INADDR_ANY);
   // nsocket.set_listening(10);
    cout<<"started"<<endl;
    return 0;
}
*/
