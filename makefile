CXX=g++ -std=c++20 -Wall -Wformat -Wreorder -lGL -lGLU -lglut -lm -ldl -lGLEW -lX11 -lpthread -lXrandr -lXi -lglfw 

OBJ=main.cpp
OBJ+=shader.cpp
OBJ+=shaderprogram.cpp
# OBJ+=shadertree.cpp

all:
	$(CXX) $(OBJ) -o VisualEngine
