//
// Created by kostdani on 6/12/21.
//

#include "HTTPServer.h"


HTTPServer::HTTPServer():m_epoller() {

}

bool HTTPServer::Start() {
    m_stopper=new Counter();
    m_epoller.AddActor(m_stopper);

    m_stop=false;
    for (int i = 1; i < thrn; ++i) {
        m_threads.emplace_back(&HTTPServer::threadfunction,this,i);
    }
    threadfunction(0);
    return true;
}

bool HTTPServer::Stop() {
    if(!m_stop){
        m_stop= true;
        m_stopper->Add(1);
        for (auto & thr:m_threads)
            thr.join();
        return true;
    }
    return false;
}

void HTTPServer::threadfunction(int threadi) {
    while (!m_stop){

        auto ev= m_epoller.getEvent();
        Actor *actor=(Actor *)ev.data.ptr;
        if((ev.events&EPOLLERR)||(ev.events&EPOLLHUP)||(ev.events&EPOLLRDHUP)){
            actor->onError(threadi);
        }else{
            if(ev.events&EPOLLIN)
                actor->onInput(threadi);
            if(ev.events&EPOLLOUT)
                actor->onOutput(threadi);

        }
    }
}

void clearstring(std::string &str){
    for (int i = 0; i < str.length(); ++i) {
        if(isspace(str[i])){
            str.erase(i,1);
            i--;
        }
    }
}


bool HTTPServer::LoadThreads(std::map<std::string, std::string> &cfgmap) {
    auto it=cfgmap.find("threads");
    if(it!=cfgmap.end()){

        int threads=std::stoi(it->second);
        if(threads>0) {
            thrn = threads;
            return true;
        }else
            return false;

    }else{
        return true;
    }
}

bool HTTPServer::LoadLogfile(std::map<std::string, std::string> &cfgmap) {

    auto it=cfgmap.find("logfile");
    if(it!=cfgmap.end()){
        clearstring(it->second);
        m_logger=new Logger(it->second);
    }else{
        m_logger=new ConsoleLogger();
    }

    m_epoller.AddActor(m_logger);
    return true;
}

bool HTTPServer::LoadListen(std::map<std::string, std::string> &cfgmap) {
    auto it=cfgmap.find("listen");
    if(it!=cfgmap.end()){
        clearstring(it->second);
        std::stringstream ss(it->second);
        std::string ip,port;
        getline(ss,ip,':');
        getline(ss,port);
        int iport=std::stoi(port);

        auto ac=new Accepter(m_logger,m_content,ip.c_str(),iport);
        m_epoller.AddActor(ac);
        return true;
    }else{
        printf("no logfile\n");
        return false;
    }
}

bool HTTPServer::LoadVirtualfs(std::map<std::string, std::string> &cfgmap)  {
    auto it=cfgmap.find("virtualfs");
    if(it!=cfgmap.end()){
        clearstring(it->second);
        std::stringstream ss(it->second);
        std::string t;
        getline(ss,t,'{');
        auto virtualdir=new VirtualDirrectoryContent();
        m_epoller.AddActor(virtualdir);
        while(true) {
            std::string line;
            getline(ss, line, ',');
            if(line.empty())
                break;
            std::string url,content;
            std::stringstream str(line);
            getline(str,url,'=');
            getline(str,content,'}');
            //str>>url>>content;
            if(content[0]=='\"'){
                std::stringstream stream(content);
                std::string path;
                getline(stream,path,'\"');
                getline(stream,path,'\"');
                auto dir=new DirectoryContent(path);
                m_epoller.AddActor(dir);
                virtualdir->AddLocation(url,dir);
            }else if(content=="terminator"){
                auto term=new TerminatorContent(m_stop,m_threads);
                m_epoller.AddActor(term);
                virtualdir->AddLocation(url,term);
            }
            //std::cout<<url<<"  "<<content<<std::endl;
        }
        m_content=virtualdir;
        return true;
    }else{
        return false;
    }
}

bool HTTPServer::LoadConfig(std::string filename) {
    std::map<std::string,std::string> configmap;
    std::ifstream file(filename);
    if(!file)
        return false;
    while(true){
        std::string key,val;
        if(!getline(file,key,' ')||!getline(file,val,';')){
            break;
        }else{
            clearstring(key);
            auto it=configmap.find(key);
            if(it!=configmap.end()){
                printf("wrong config");
                return false;
            }
            configmap[key]=val;
            //std::cout<<key<<"   "<<val<<std::endl;
        }

    }

return LoadThreads(configmap) && LoadLogfile(configmap) &&  LoadVirtualfs(configmap) && LoadListen(configmap);


}