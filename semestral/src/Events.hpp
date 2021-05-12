#ifndef EVENTSERVER_EVENTS_H
#define EVENTSERVER_EVENTS_H
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/timerfd.h>
#include <sys/eventfd.h>

#include <memory>
#include <vector>


namespace Events {

    class BaseEvent {
    public:
        // Constructor
        BaseEvent(int d);
        // Check if descriptor is ok
        bool Check() const;
        // Close descriptor
        void Close();

        virtual int Execute();
        virtual bool Multiplex(int epolldf);
    protected:


        int m_descriptor;
    };


    // Wrapper for eventfd
    class Counter:public BaseEvent{
    public:
        // Constructor
        Counter();
        // Increment counter
        void Inc();
        // Reset counter
        void Reset();

        int Execute() override;
        bool Multiplex(int epolldf) override;
    protected:


    };
    // Wrapper for timerfd
    class Timer:public BaseEvent{
    public:
        // Constructor
        Timer(timespec timeout={});
        // Sets Timeout
        void SetTimeout(timespec timeout);
        // Resets timer
        void ResetTimer();

        bool Multiplex(int epolldf) override;

        int Execute() override;

    protected:
        timespec m_timeout;
    };
    class IOEvent: public BaseEvent{
    public:
        IOEvent(int descriptor);
        bool Ready() const;
    protected:
        bool m_ready=false;
    };
    class InEvent: public IOEvent{
    public:

        InEvent(int descriptor);

        bool Multiplex(int epolldf) override;

        int Execute() override;
    };
    class OutEvent: public IOEvent{
    public:

        OutEvent(int descriptor);

        bool Multiplex(int epolldf) override;

        int Execute() override;
    };
    std::pair<InEvent,OutEvent> MakePipe();

    // wrapper for epoll
    class Epoller :public BaseEvent{
    public:
        // Constructor
        Epoller();


        int Execute() override;
    private:

    };


    class DynamicEpoller:public Epoller{
    public:
        DynamicEpoller();

        // Add descriptor to epoll
        void Add(std::shared_ptr<BaseEvent> event);

        int Execute() override;
    protected:
        // array of listened evvents
        std::vector<std::shared_ptr<BaseEvent>> m_event;
    };
    // if in is awailable for read and out is awailable for write pump data through
    class Pumper:public Epoller{
    public:
        Pumper(int in=-1,int out=-1);

        int Execute() override;
    protected:
        InEvent m_in;
        OutEvent m_out;
    };

    // wrapper for input, output and timeout of a client
    class Clienter:Epoller{
    public:
        Clienter(int decriptor,sockaddr_in addr);

        int Execute() override;
    protected:
        Pumper reader;
        Pumper handler;
        Pumper writer;
        Timer timer;
        sockaddr_in m_cli_addr;
    };

    // wrapper for server tcp socket
    class Accepter: public BaseEvent{
    public:
        Accepter(sockaddr_in addr);

        Accepter(const char * ip="127.0.0.1",int port=80);

        int Execute() override;
    };




}


#endif //EVENTSERVER_EVENTS_H
