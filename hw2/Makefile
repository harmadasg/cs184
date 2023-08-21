CC = g++

CFLAGS = -g -DGL_GLEXT_PROTOTYPES 
INCFLAGS = -I/usr/X11R6/include -I/sw/include \
		-I/usr/sww/include -I/usr/sww/pkg/Mesa/include
LDFLAGS = -L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib \
		-L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib -lglut -lGLU -lGL -lX11

RM = /bin/rm -f 
all: transform
transform: main.o shaders.o Transform.o readfile.o display.o variables.h readfile.h shaders.h Transform.h
	$(CC) $(CFLAGS) -o transforms shaders.o main.o Transform.o readfile.o display.o $(INCFLAGS) $(LDFLAGS) 
main.o: main.cpp shaders.h Transform.h variables.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp
shaders.o: shaders.cpp shaders.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c shaders.cpp
readfile.o: readfile.cpp readfile.h variables.h 
	$(CC) $(CFLAGS) $(INCFLAGS) -c readfile.cpp
display.o: display.cpp variables.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c display.cpp
Transform.o: Transform.cpp Transform.h 
	$(CC) $(CFLAGS) $(INCFLAGS) -c Transform.cpp  
clean: 
	$(RM) *.o transforms *.png


 
