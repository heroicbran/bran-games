cyoa: server.cpp client.cpp
	g++ -std=c++11 server.cpp -lrpc -lpthread -o server
	g++ -std=c++11 client.cpp -lrpc -lpthread -w -lSDL2 -lSDL2_image -o client

.PHONY: clean

clean: server client
	rm server
	rm client
