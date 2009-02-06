.PHONY : clean rebuild install uninstall

FLAGS=-Wall -g

CC=g++

TARGET=a2l

LIBS=-lbfd -lboost_iostreams-mt

SRC=main.cc addr2line.cc

OBJ=$(SRC:.cc=.o)

all: $(SRC) $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) $(LIBS) -o $@
	gcc -g addr2line2.c -o a2l2 -lbfd

.cc.o:
	$(CC) $(FLAGS) $< -c

run:
	@./$(TARGET) ~/work/sirena/sirenalibs/serverlib/testapp 0x81b3fcb
	@addr2line -e ~/work/sirena/sirenalibs/serverlib/testapp 0x81b3fcb

clean:
	rm -f *.o $(TARGET)

