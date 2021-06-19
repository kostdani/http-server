CC=g++
CFLAGS=-lpthread -std=c++14 -Wall -pedantic -Wno-long-long -O2 -Werror -fsanitize=address


all: compile doc

run:	compile
	./kostdani examples/server.cfg

compile: src/build/main.o src/build/Accepter.o src/build/Actor.o src/build/FileLogger.o src/build/ContentGenerator.o src/build/Counter.o src/build/DirectoryContent.o src/build/Epoller.o src/build/FileContent.o src/build/HTTPRequest.o src/build/HTTPServer.o src/build/Logger.o src/build/Queuer.o src/build/Reciever.o src/build/Sender.o src/build/TerminatorContent.o src/build/Timer.o src/build/VirtualDirrectoryContent.o
	$(CC) $(CFLAGS) $^ -o kostdani


doc: Doxyfile README.md src/Accepter.h src/Epoller.h src/Reciever.h src/Actor.h src/FileContent.h src/FileLogger.h src/HTTPRequest.h src/Sender.h src/ContentGenerator.h src/HTTPServer.h src/TerminatorContent.h src/Counter.h src/Logger.h src/Timer.h src/DirectoryContent.h src/Queuer.h src/VirtualDirrectoryContent.h
	mkdir -p doc
	doxygen $<

src/build/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

src/build/Accepter.o: src/Accepter.cpp src/Accepter.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/Actor.o: src/Actor.cpp src/Actor.h 
	$(CC) $(CFLAGS) -c $< -o $@

src/build/FileLogger.o: src/FileLogger.cpp src/FileLogger.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/ContentGenerator.o: src/ContentGenerator.cpp src/ContentGenerator.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/Counter.o: src/Counter.cpp src/Counter.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/DirectoryContent.o: src/DirectoryContent.cpp src/DirectoryContent.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/Epoller.o: src/Epoller.cpp src/Epoller.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/FileContent.o: src/FileContent.cpp src/FileContent.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/HTTPRequest.o: src/HTTPRequest.cpp src/HTTPRequest.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/HTTPServer.o: src/HTTPServer.cpp src/HTTPServer.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/Logger.o: src/Logger.cpp src/Logger.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/Queuer.o: src/Queuer.cpp src/Queuer.h src/Queuer.ipp
	$(CC) $(CFLAGS) -c $< -o $@

src/build/Reciever.o: src/Reciever.cpp src/Reciever.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/Sender.o: src/Sender.cpp src/Sender.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/TerminatorContent.o: src/TerminatorContent.cpp src/TerminatorContent.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/Timer.o: src/Timer.cpp src/Timer.h
	$(CC) $(CFLAGS) -c $< -o $@

src/build/VirtualDirrectoryContent.o: src/VirtualDirrectoryContent.cpp src/VirtualDirrectoryContent.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf src/build/* kostdani
