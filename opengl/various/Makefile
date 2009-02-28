.PHONY : clean rebuild

GL_FLAGS=-I/usr/X11/include
GL_LIBS=-L/usr/X11/lib -lGLU -lglut

all: yinyang3d

2d:
	g++ main2d.cpp -o 2d $(GL_LIBS)

3d:
	g++ main3d.cpp -o 3d $(GL_LIBS)

yinyang:
	g++ yinyang.cc -o yinyang $(GL_LIBS)

yinyang3d:
	g++ yinyang3d.cpp -o yinyang3d $(GL_LIBS)

select:
	g++ select.cpp -o select $(GL_LIBS)

clean:
	rm -f yinyang yinyang3d 2d 3d *.o

rebuild: clean all
	
