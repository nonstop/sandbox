.PHONY : clean rebuild install uninstall

FLAGS=-Wall -I/usr/local/include/boost-1_35
CC=g++
TARGET=threads
LIBS=-lstdc++ -lboost_thread-gcc40-mt
SRC=main.cpp
OBJ=$(SRC:.cpp=.o)

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $@

.cpp.o:
	$(CC) $(FLAGS) $< -c

clean:
	rm -f *.o $(TARGET)

