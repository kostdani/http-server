CC=g++
CFLAGS=-lpthread -Wall

all: compile

compile: build/main.o build/Accepter.o build/Actor.o build/ConsoleLogger.o build/ContentGenerator.o build/Counter.o build/DirectoryContent.o build/Epoller.o build/FileContent.o build/HTTPRequest.o build/HTTPServer.o build/Logger.o build/Queuer.o build/Reciever.o build/Sender.o build/TerminatorContent.o build/Timer.o build/VirtualDirrectoryContent.o
	$(CC) $(CFLAGS) $^ -o Server

build/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

build/Accepter.o: src/Accepter.cpp src/Accepter.h
	$(CC) $(CFLAGS) -c $< -o $@

build/Actor.o: src/Actor.cpp src/Actor.h 
	$(CC) $(CFLAGS) -c $< -o $@

build/ConsoleLogger.o: src/ConsoleLogger.cpp src/ConsoleLogger.h
	$(CC) $(CFLAGS) -c $< -o $@

build/ContentGenerator.o: src/ContentGenerator.cpp src/ContentGenerator.h
	$(CC) $(CFLAGS) -c $< -o $@

build/Counter.o: src/Counter.cpp src/Counter.h
	$(CC) $(CFLAGS) -c $< -o $@

build/DirectoryContent.o: src/DirectoryContent.cpp src/DirectoryContent.h
	$(CC) $(CFLAGS) -c $< -o $@

build/Epoller.o: src/Epoller.cpp src/Epoller.h
	$(CC) $(CFLAGS) -c $< -o $@

build/FileContent.o: src/FileContent.cpp src/FileContent.h
	$(CC) $(CFLAGS) -c $< -o $@

build/HTTPRequest.o: src/HTTPRequest.cpp src/HTTPRequest.h
	$(CC) $(CFLAGS) -c $< -o $@

build/HTTPServer.o: src/HTTPServer.cpp src/HTTPServer.h
	$(CC) $(CFLAGS) -c $< -o $@

build/Logger.o: src/Logger.cpp src/Logger.h
	$(CC) $(CFLAGS) -c $< -o $@

build/Queuer.o: src/Queuer.cpp src/Queuer.h
	$(CC) $(CFLAGS) -c $< -o $@

build/Reciever.o: src/Reciever.cpp src/Reciever.h
	$(CC) $(CFLAGS) -c $< -o $@

build/Sender.o: src/Sender.cpp src/Sender.h
	$(CC) $(CFLAGS) -c $< -o $@

build/TerminatorContent.o: src/TerminatorContent.cpp src/TerminatorContent.h
	$(CC) $(CFLAGS) -c $< -o $@

build/Timer.o: src/Timer.cpp src/Timer.h
	$(CC) $(CFLAGS) -c $< -o $@

build/VirtualDirrectoryContent.o: src/VirtualDirrectoryContent.cpp src/VirtualDirrectoryContent.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build Server
