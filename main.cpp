#include <iostream>
#include <chrono>
#include <cmath>

// #include "shadertree.h"
#include "triangle.h"
#include "engine.h"

namespace ch = std::chrono;

using WndPtr = GLFWwindow*;

int main()
{
    system("clear");

    vertex_t vert_1 = std::make_shared<glm::vec3>(glm::vec3(-0.5f, -0.5f, 0.0f));
    vertex_t vert_2 = std::make_shared<glm::vec3>(glm::vec3(0.5f, -0.5f, 0.0f));
    vertex_t vert_3 = std::make_shared<glm::vec3>(glm::vec3(0.0f, 0.5f, 0.0f));
    
    Triangle tr1 (vert_1, vert_2, vert_3);
    
    Object3D* tr = &tr1;

    Engine::engine().run(tr);

	return 0;
}
