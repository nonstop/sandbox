.PHONY : clean rebuild install uninstall

FLAGS=-Wall

CC=g++

TARGET=shared

LIBS=-lboost_system

all: dispatcher

dispatcher: dispatcher.cc utils.h
	$(CC) $< $(FLAGS) $(LIBS) -o $@

clean:
	rm -f *.o dispatcher

