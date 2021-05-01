#include "server.hpp"

#include <sstream>

MyServer::Server::Server(){
    
}

bool MyServer::Server::Setup(ulong addr, int port ){
    m_stop=false;
    sockaddr_in stSockAddr;
	stSockAddr.sin_family = PF_INET;
	stSockAddr.sin_port = htons(port);
	stSockAddr.sin_addr.s_addr = htonl(addr);

    
    m_socket = std::make_shared<MyServer::Socket>(socket(PF_INET,SOCK_STREAM,0),stSockAddr );
    if(!m_socket->Check_Socket()){
        printf("cannot create socket\n");
        return false;
    }
    if(!m_socket->Bind(stSockAddr)){
        printf("cannot bind socket\n");
        return false;
    }
    
    return true;
}

bool MyServer::Server::Start(int workerthreadn,int mediatorthreadn){
    std::cout<<"starting\n";
    m_stop=false;
    if(!m_socket)
        return false;
    
    m_socket->Listen(mediatorthreadn);
    std::cout<<"listening\n";
    
    for(int i=0;i<workerthreadn;++i){
        workers.emplace_back(&MyServer::Server::workerfunc,this);
    }
    
    for(int i=0;i<mediatorthreadn;++i){
        workers.emplace_back(&MyServer::Server::mediatorfunc,this);
    }
    std::cout<<"started\n";
    return true;
}


void MyServer::Server::Stop() {
    std::cout<<"stopping\n";
    m_stop=true;
    cvw.notify_all();
    for(auto &thr:mediators){
        thr.join();
    }
    for(auto &thr:workers){
        thr.join();
    }
    
                printf("worker end\n");
    
}


void MyServer::Server::workerfunc() {
    while(1){
        if(work.empty()){
    std::cout<<"no work hanging up\n";
            std::unique_lock<std::mutex> locker(mw);
            cvw.wait(locker);
           
        }
        if(m_stop)
            break;
        workmtx.lock();
        if(work.empty()){
            workmtx.unlock();
            continue;
        }
    std::cout<<"woke up\n";
        std::string s=work.back();
        work.pop_back();
        workmtx.unlock();
        std::cout<<s<<std::endl;
        
    }
}


void MyServer::Server::mediatorfunc() {
    while(1){
        if(m_stop)
            break;
        
        printf("trying accept\n");
        auto sock=m_socket->Accept();
      
        if(m_stop)
            break;
        if(!sock)
            continue;
        printf("acepted connection\n");
        while(1){
            printf("trying to read\n");
            if(m_stop){
                printf("mediator end\n");
                return;
                
            }
            std::ostringstream ts("");
            ts<<(*sock);
            std::cout<<"red "<<ts.str().size()<<"bytes\n";
            if(!ts.str().empty()){
                work.push_back(ts.str());
                cvw.notify_all();
            }
            if(!sock->Check_Connection()){
                printf("connection lost\n");
                break;
            }
        }
    }
    
                printf("mediator end\n");
}
