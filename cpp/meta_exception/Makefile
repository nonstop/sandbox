.PHONY : clean rebuild install uninstall

FLAGS=-Wall

CC=g++

TARGET=test

LIBS=

SRC=test.cpp callstack.cpp

OBJ=$(SRC:.cpp=.o)

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $@

.cpp.o:
	$(CC) $(FLAGS) $< -c

clean:
	rm -f *.o $(TARGET)

