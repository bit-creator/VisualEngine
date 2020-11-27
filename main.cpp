#include <iostream>
#include <chrono>
#include <cmath>

// #include "GL/shadertree.h"
// #include "Primitive/triangle.h"
#include "engine.h"
// #include "Primitive/rect.h"
#include "Primitive/sphere.h"
#include "GL/vertexarray.h"

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
        
        auto color = glm::vec4(f1, f2, f3, 1.0);
        auto color_ = glm::vec4(f2, f1, f3, 1.0); 
        
        _object.getMaterial() -> setColor(ColorTarget::Ambient, color);
        _object.getMaterial() -> setColor(ColorTarget::Diffuse, color);
        _object.getMaterial() -> setColor(ColorTarget::Specular, color_);
        _object.getMaterial() -> setRoughness(0.1);
        _object.getMaterial() -> setPolygonsFillMode(GL_FILL);

        _object.setScale(glm::vec3(0.5f, 0.5f, 0.5f));

        _object.setRotate(glm::vec3(1., 1., 1.), f4);

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

    // vertex_t 1 = glm::vec3(-0.5f, -0.5f, 0.0f);
    // vertex_t 2 = glm::vec3(0.5f, -0.5f, 0.0f);
    // vertex_t 3 = glm::vec3(-0.5f, 0.5f, 0.0f);
    // vertex_t 4 = glm::vec3(0.5f, 0.5f, 0.0f);
    


    
    MaterialPtr simple = std::make_shared<Material>();
        
    Sphere sphere(5);
    
    sphere.setMaterial(simple);

    MyListener listener(sphere);

    eng.addEventListener(std::make_shared<MyListener>(listener));

    eng.engine().run(&sphere);

    return 0;
}
