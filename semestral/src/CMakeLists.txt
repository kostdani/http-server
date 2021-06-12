cmake_minimum_required(VERSION 3.19)
project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(Server main.cpp Epoller.cpp Epoller.h Actor.cpp Actor.h Accepter.cpp Accepter.h Client.cpp Client.h Counter.cpp Counter.h Reciever.cpp Reciever.h Timer.cpp Timer.h Queuer.cpp Queuer.h Message.cpp Message.h Sender.cpp Sender.h HTTPServer.cpp HTTPServer.h)