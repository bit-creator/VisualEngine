CXX=g++ -std=c++20 -Wall -Wformat -Wreorder -lGL -lGLU -lglut -lm -ldl -lGLEW -lX11 -lpthread -lXrandr -lXi -lglfw 

OBJ=main.cpp
OBJ+=GL/shader.cpp
OBJ+=GL/shaderprogram.cpp
# OBJ+=GL/shadertree.cpp
OBJ+=object3d.cpp
OBJ+=Primitive/triangle.cpp
OBJ+=window.cpp
OBJ+=engine.cpp
OBJ+=Primitive/rect.cpp
OBJ+=GL/buffer.cpp
OBJ+=Primitive/sphere.cpp

all:
	$(CXX) $(OBJ) -o VisualEngine
