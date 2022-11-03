# -----------------------------------------------------------------------------
# Onset Engine
# https://github.com/dylanafterall/OnsetEngine.git
#
# Makefile
#  build system for Mesh Formatter tool
# -----------------------------------------------------------------------------

CC = g++
CFLAGS = -std=c++17
INC_PATH = -Iexternal/glm/
LIBS =

TARGET = ./formatter
SRC_FILES = ./main.cpp \
			./mesh_formatter.cpp
OBJ_FILES = ./main.o \
			./mesh_formatter.o


#-------------------------------------------------------------------------------
# make                  makes executable
# make build			compiles .o files, doesn't link into executable
# make clean            removes all object files and executable
#-------------------------------------------------------------------------------


# make -------------------------------------------------------------------------
formatter :
	$(CC) $(CFLAGS) $(INC_PATH) $(SRC_FILES) $(LIBS) -o $(TARGET)


# make build -------------------------------------------------------------------
build : $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LIBS) -o $(TARGET)

main.o : ./main.cpp
	$(CC) $(CFLAGS) $(INC_PATH) -c ./main.cpp -o ./main.o

mesh_formatter.o : ./mesh_formatter.cpp ./mesh_formatter.hpp
	$(CC) $(CFLAGS) $(INC_PATH) -c ./mesh_formatter.cpp -o ./mesh_formatter.o


# make clean -------------------------------------------------------------------
clean :
	rm -f $(TARGET) $(OBJ_FILES)