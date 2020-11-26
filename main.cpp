#include <iostream>
#include <chrono>
#include <cmath>

// #include "GL/shadertree.h"
#include "Primitive/triangle.h"
#include "engine.h"
#include "Primitive/rect.h"
#include "Primitive/sphere.h"

namespace ch = std::chrono;

using WndPtr = GLFWwindow *;

using ObjPtr = std::shared_ptr<Object3D>;

class MyListener : public EventListener
{
    Object3D& _object;

public:
    MyListener(Object3D& obj)
        : _object(obj)
    {
    }

    void onRender() noexcept override
    {
        static double time =0;
        // auto current_time = ch::high_resolution_clock().now();
        // auto count = duration_cast<ch::seconds>((time_point)current_time).count();

        float f1 = std::abs(std::sin(1 * time));
        float f2 = std::abs(std::sin(2 * time));
        float f3 = std::abs(std::sin(3 * time));
        float f4 = time;

        time += 0.001;

        _object.setColor(colour_t(1., 0.2, 0.2, 1.0));

        _object.setScale(glm::vec3(1.f, 1.f, 1.f));

        _object.setRotate(glm::vec3(0., 1., 0.), 0.);

        _object.setOffset(glm::vec3(0., 0., 0.));
    }

    ~MyListener() override {
    }

};

int main()
{
    system("clear");

    // ShaderTree::get().initShaderTree("shaders");

    auto& eng = Engine::engine();

    vertex_t vert_1 = glm::vec3(-0.5f, -0.5f, 0.0f);
    vertex_t vert_2 = glm::vec3(0.5f, -0.5f, 0.0f);
    vertex_t vert_3 = glm::vec3(-0.5f, 0.5f, 0.0f);
    vertex_t vert_4 = glm::vec3(0.5f, 0.5f, 0.0f);
    

    // Rect tr1;

    Sphere tr1(0.5, 1);

    MyListener listener(tr1);

    eng.addEventListener(std::make_shared<MyListener>(listener));

    // eng._eventListener = std::make_shared<MyListener>(MyListener(tr1));

    eng.engine().run(&tr1);

    return 0;
}
