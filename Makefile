# OBJS specifies which files to compile as part of the project
# OBJS = src/main.cc src/Game.cc src/TextureManager.cc src/SDLGameObject.cc src/Player.cc src/InputHandler.cc src/MenuState.cc src/PlayState.cc src/GameStateMachine.cc src/MenuButton.cc src/PauseState.cc src/Enemy.cc src/GameOverState.cc
OBJS = source/*.cc tinyxml/*.cpp
# CC specifies which compiler we're using
CC = g++

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all wanings
# -std=c++11 using standard c++11
COMPILER_FLAGS = -std=c++11 -g -I include/ -I tinyxml/

# LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_mixer

# OBJ_NAME specifies the name of our exectuable
OBJ_NAME = snake 

# This is the target that compilers our executable
all : $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
