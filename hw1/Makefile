CC = g++

CFLAGS = -g -DGL_GLEXT_PROTOTYPES 
INCFLAGS = -I./include/ -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib \
		-L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lglut -lGLU -lGL -lX11
RM = /bin/rm -f 
all: transform

transform: main.o shaders.o Transform.o shaders.h Transform.h
	$(CC) $(CFLAGS) -o transforms shaders.o main.o Transform.o $(INCFLAGS) $(LDFLAGS) 
main.o: main.cpp shaders.h Transform.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
shaders.o: shaders.cpp shaders.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c shaders.cpp
Transform.o: Transform.cpp Transform.h 
	$(CC) $(CFLAGS) $(INCFLAGS) -c Transform.cpp
clean: 
	$(RM) *.o transforms
