.PHONY : clean rebuild install uninstall

FLAGS=-Wall

CC=g++

TARGET=shared

LIBS=-lrt

SRC=shared.cpp

OBJ=$(SRC:.cpp=.o)

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $@

.cpp.o:
	$(CC) $(FLAGS) $< -c

clean:
	rm -f *.o $(TARGET)

