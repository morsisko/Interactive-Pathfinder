PATH_TO_SFML_INCLUDE = .
PATH_TO_SFML_LIBS = .

CC = g++
SRC_DIR = ./Pathfinder
SRCS    = $(wildcard $(SRC_DIR)/*.cpp)
OUT_APP = PathfinderApp
LIB_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

build:
	$(CC) $(SRCS) -I$(PATH_TO_SFML_INCLUDE) -L$(PATH_TO_SFML_LIBS) -o $(OUT_APP) $(LIB_FLAGS)
	cp -n $(SRC_DIR)/config.ini $(SRC_DIR)/arial.ttf .
