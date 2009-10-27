.PHONY : clean rebuild

FLAGS=-Wall

CC=gcc

all: udpserver udpclient

udpserver: udpserver.c
	$(CC) udpserver.c -o $@

udpclient: udpclient.c
	$(CC) udpclient.c -o $@

clean:
	rm -f *.o udpserver udpclient



