#include "sockets.cpp"
#include <thread>
#include <vector>
#include <condition_variable>


namespace MyServer{
    

    
    class Server{
    public:
        Server();
        bool Setup(ulong addr=INADDR_ANY,int port=8080);
        bool Start(int workerthreadn,int mediatorthreadn);
        void Stop();
    private:
        bool m_stop;
        std::vector<std::thread> workers;
        std::vector<std::thread> mediators;

        std::shared_ptr<MyServer::Socket> m_socket;
    
        std::vector<std::string> work;

        std::mutex mw;
        std::condition_variable cvw;

        
        std::mutex workmtx;
        
        void workerfunc();
        void mediatorfunc();
    
    };
    
    

}
