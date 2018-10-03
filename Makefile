OBJS = src/*.cpp

CC = g++

COMPILER_FLAGS = -w -Iheaders
#-Wall -Werror -Wextra -pedantic -Isrc/headers

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer

OBJ_NAME = the_maze

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
