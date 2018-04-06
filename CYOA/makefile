server: server.cpp
	g++ -std=c++11 server.cpp -lrpc -lpthread -o server

.PHONY: clean

clean: server ./peer1/peer1 ./peer2/peer2 ./peer3/peer3 ./peer4/peer4
	rm server
