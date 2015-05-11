all: server client

CFLAGS=-std=c++11 -Wall -g 
LD_FLAGS=-lcrypto -lssl -lboost_system


server: server.cc
	clang++ $(CFLAGS) server.cc $(LD_FLAGS) -o server

client: client.cc
	clang++ $(CFLAGS) client.cc $(LD_FLAGS) -pthread -o client

keys:
	openssl genrsa -out privkey.pem
	openssl req -new -x509 -key privkey.pem -out cert.pem -days 1095

