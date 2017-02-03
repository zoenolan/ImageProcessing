CC = g++

CFLAGS = -O3

INCLUDES = -I/usr/share/src/OpenGL/libaux

GL_LIBS =-lGLU -lGL -L/usr/share/src/OpenGL/libaux -laux
X11_LIBS = -lX11 -lXext
EXTRA_LIBS = -lm
LIBS = $(GL_LIBS) $(X11_LIBS) $(EXTRA_LIBS)

test:main.o colour.o pixmap.o mask.o
	$(CC) $(INCLUDES) $(CFLAGS) colour.o mask.o pixmap.o main.o -o tester $(GL_LIBS) $(X11_LIBS) $(EXTRA_LIBS)

main.o:main.cpp
	$(CC) $(INCLUDES) -c main.cpp

colour.cpp:colour.h
	touch colour.cpp

colour.o:colour.cpp
	$(CC) -c colour.cpp

pixmap.cpp:pixmap.h colour.h
	touch pixmap.cpp

pixmap.o:pixmap.cpp
	$(CC) $(INCLUDES) -c pixmap.cpp

main.cpp:pixmap.h
	touch main.cpp

mask.o:mask.cpp
	$(CC) -c mask.cpp

mask.cpp:mask.h
	touch mask.cpp
