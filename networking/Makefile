
#all: udp tcp asio confirm
all: confirm

udp:
	gcc udp-client.c -o udp-client
	gcc udp-server.c -o udp-server

tcp:
	g++ tcp-client.cc -o tcp-client
	g++ tcp-server.cc -o tcp-server

asio:
	g++ asio-client.cc -o asio-client -lboost_regex-gcc-1_33_1 -lboost_thread-gcc-mt-1_33_1

confirm:
	g++ confirm-client.cc -o confirm-client -lboost_regex-gcc-1_33_1 -lboost_thread-gcc-mt-1_33_1
	g++ confirm-server.cc -o confirm-server -lboost_regex-gcc-1_33_1 -lboost_thread-gcc-mt-1_33_1

