cmake_minimum_required(VERSION 3.19)
project(Server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(Server main.cpp Epoller.cpp Epoller.h Actor.cpp Actor.h Accepter.cpp Accepter.h Counter.cpp Counter.h Reciever.cpp Reciever.h Timer.cpp Timer.h Queuer.cpp Queuer.h Sender.cpp Sender.h HTTPServer.cpp HTTPServer.h Logger.cpp Logger.h HTTPRequest.cpp HTTPRequest.h ContentGenerator.cpp ContentGenerator.h FileContent.cpp FileContent.h DirectoryContent.cpp DirectoryContent.h TerminatorContent.cpp TerminatorContent.h VirtualDirrectoryContent.cpp VirtualDirrectoryContent.h ScriptContent.cpp ScriptContent.h ConsoleLogger.cpp ConsoleLogger.h)