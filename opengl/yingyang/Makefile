.PHONY : clean rebuild

GL_FLAGS=-I/usr/X11/include
GL_LIBS=-L/usr/X11/lib -lGLU -lglut


all: yinyang

yinyang:
	g++ yinyang3d.cpp -o yinyang3d $(GL_LIBS)

clean:
	rm -f yinyang yinyang3d 2d 3d *.o

rebuild: clean all

