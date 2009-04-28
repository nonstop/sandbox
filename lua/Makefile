.PHONY : clean rebuild install uninstall

FLAGS=-Wall

CC=gcc

TARGET=testLua

LIBS=-llua -ldl -lm

SRC=lua.c

OBJ=$(SRC:.c=.o)

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $@

..o:
	$(CC) $(FLAGS) $< -c

clean:
	rm -f *.o $(TARGET)


