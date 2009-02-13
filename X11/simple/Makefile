.PHONY : clean rebuild install uninstall

INCLUDES=-I/usr/X11R6/include
FLAGS=-Wall $(INCLUDES)

CC=g++

TARGET=simpleWindow

LIBS=-lX11 -L/usr/X11R6/lib

SRC=simpleWindow.cpp

OBJ=$(SRC:.cpp=.o)

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $@

.cpp.o:
	$(CC) $(FLAGS) $< -c

clean:
	rm -f *.o $(TARGET)

