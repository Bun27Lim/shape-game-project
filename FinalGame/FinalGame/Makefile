# A simple Makefile for SDL projects

# set the compiler
CC = g++

# set the compiler flags
CFLAGS = `sdl2-config --libs --cflags` -ggdb3 -O0 -Wall -lSDL2_image -lm 

# add header files here
HDRS = Accuracy.h AudioManager.h BGLayer.h EndScreen.h GameEngine.h GameObject.h Particle.h ParticleEmitter.h PauseMenu.h screenInfo.h TextObject.h TextureManager.h TitleScreen.h

# add source files here
SRCS = Accuracy.cpp AudioManager.cpp BGLayer.cpp EndScreen.cpp GameEngine.cpp GameObject.cpp Particle.cpp ParticleEmitter.cpp PauseMenu.cpp TextObject.cpp TextureManager.cpp TitleScreen.cpp

# generate names of object files
OBJS = $(SRCS:.cpp=.o)

# name of executable
EXEC = my_game

# default recipe
all: $(EXEC)
 
#showfont: showfont.c Makefile
#    $(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

#glfont: glfont.c Makefile
#    $(CC) -o $@ $@.c $(CFLAGS) $(LIBS)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe for building object files
$(OBJS): $(@:.o=.cpp) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.cpp) -c $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) 
	rm -f $(OBJS)

