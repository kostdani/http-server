//
// Created by kostdani on 6/12/21.
//

#include "HTTPServer.h"


bool HTTPServer::Start() {
    if(!m_stop)
        return false;
    m_stop=false;
    while (!m_stop){
        auto ev= m_epoller.GetEvent();
        auto *actor=static_cast<Actor *>(ev.data.ptr);
        try{
            actor->Run(ev.events);
        }catch (std::exception &exc){
            m_epoller.RmActor(actor);
        }
    }
    return true;
}

bool HTTPServer::LoadLogfile(const std::map<std::string, std::string> &cfgmap) {

    auto it=cfgmap.find("logfile");
    if(it!=cfgmap.end()){

        std::ofstream of(it->second);
        if(!of.is_open())
            return false;
        of.close();
        m_logger=new FileLogger(it->second);
    }else{
        m_logger=new Logger();
    }

    m_epoller.AddActor(m_logger);
    return true;
}

bool HTTPServer::LoadListen(const std::map<std::string, std::string> &cfgmap) {
    auto it=cfgmap.find("listen");
    if(it!=cfgmap.end()){
        std::stringstream ss(it->second);
        std::string ip,port;
        getline(ss,ip,':');
        getline(ss,port);
        int iport=std::stoi(port);
        try{
            m_epoller.AddActor(new Accepter(m_logger,m_content,ip.c_str(),iport));
            return true;
        }catch(...){
            return false;
        }
    }else{
        return false;
    }
}

bool HTTPServer::LoadVirtualfs(const std::map<std::string, std::string> &cfgmap)  {
    auto it=cfgmap.find("virtualfs");
    if(it!=cfgmap.end()){
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
            std::string url,contype,content;
            std::stringstream str(line);
            getline(str,url,'=');
            getline(str,contype,':');
            getline(str,content,'}');
            //str>>url>>content;
            ContentGenerator *gen= nullptr;
            if(contype=="file"){
                gen=new FileContent(content);
            }else if(contype=="dir"){
                gen=new DirectoryContent(content);
            }else if(contype=="script"){
                gen=new ScriptContent(content);
            }else if(contype=="special"){
                if(content=="terminator"){
                    gen=new TerminatorContent(m_stop);
                }
            }
            if(gen) {
                m_epoller.AddActor(gen);
                virtualdir->AddLocation(url, gen);
            }else{
                return false;
            }
        }
        m_content=virtualdir;
        return true;
    }else{
        return false;
    }
}

bool HTTPServer::LoadConfig(const std::string& filename) {
    std::map<std::string,std::string> configmap;
    std::ifstream file(filename);
    if(!file)
        return false;
    while(true){
        std::string key,val;
        if(!getline(file,key,'=')||!getline(file,val,';')){
            break;
        }else{
            key={key.begin(),std::remove_if( key.begin(), key.end(), isspace )};
            val={val.begin(),std::remove_if( val.begin(), val.end(), isspace )};
            auto it=configmap.find(key);
            if(it!=configmap.end())
                return false;
            configmap[key]=val;
        }
    }
return LoadLogfile(configmap) &&  LoadVirtualfs(configmap) && LoadListen(configmap);
}