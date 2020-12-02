#include <iostream>
#include <chrono>
#include <cmath>

// #include "GL/shadertree.h"
#include "Primitive/triangle.h"
#include "engine.h"
#include "Primitive/rect.h"
#include "Primitive/sphere.h"
#include "GL/vertexarray.h"
#include "Primitive/circle.h"
#include "Primitive/cube.h"
#include "Primitive/cone.h"
#include "Primitive/mobiusstrip.h"

namespace ch = std::chrono;

using WndPtr = GLFWwindow *;

using ObjPtr = std::shared_ptr<Object3D>;

class MyListener : public EventListener
{
    Scene& scene;

public:
    MyListener(Scene& sc)
        : scene(sc)
    {  }

    void onRender() noexcept override
    {
        static double time =0;
        // auto current_time = ch::high_resolution_clock().now();
        // auto count = duration_cast<ch::seconds>((time_point)current_time).count();

        float f1 = std::abs(std::sin(1 * time));
        float f2 = std::abs(std::sin(2 * time));
        float f3 = std::abs(std::sin(3 * time));
        float f4 = time;

        time += 0.01;
        
        auto color = glm::vec4(1., 0.2, 0.2, 1.0);
        auto color_ = glm::vec4(1., 1., 1., 1.0); 
        
        scene._object->getMaterial() -> setColor(ColorTarget::Ambient, color);
        scene._object->getMaterial() -> setColor(ColorTarget::Diffuse, color);
        scene._object->getMaterial() -> setColor(ColorTarget::Specular, color_);
        scene._object->getMaterial() -> setRoughness(0.01);
        scene._object->getMaterial() -> setPolygonsFillMode(GL_FILL);
        scene._object->setScale(glm::vec3(1.f, 1.0f, 1.f));
        scene._object->setRotate(glm::vec3(1., 1., 1.), 0.8);
        scene._object->setPosition(glm::vec3(0.0, 0.0, 3.0));

        // scene._camera->setPosition(glm::vec3(0.0, 0.0, -1.0));
        // scene._object->setRotate(glm::vec3(1., 1., 1.), 0.0);
        // scene._object->setScale(glm::vec3(1.f, 1.0f, 1.f));
    }

    void onKeyPressed(int key, int scancode, int action, int mode) noexcept override
    {
        if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            std::cout << "|    INFO     | escape pressed\n";    
        }
    }

    ~MyListener() override {
    }

};

int main()
{
    system("clear");


    // ShaderTree::get().initShaderTree("shaders");

    auto& eng = Engine::engine();

    Scene scene;

    auto obj = std::make_shared<Object3D>();
    
    MaterialPtr simple = std::make_shared<Material>();
        
    // GeometryPtr sphere = std::make_shared<Sphere>(5);
    // GeometryPtr circle = std::make_shared<Circle>(10);
    // GeometryPtr rect = std::make_shared<Rect>();
    // GeometryPtr triangle = std::make_shared<Triangle>();
    GeometryPtr cube = std::make_shared<Cube>();
    // GeometryPtr cone = std::make_shared<Cone>(5);
    // GeometryPtr mobius = std::make_shared<MobiusStrip>(50);

    // obj.setGeometry(sphere);
    // obj.setGeometry(circle);
    // obj.setGeometry(rect);
    obj->setGeometry(cube);
    // obj.setGeometry(cone);
    // obj.setGeometry(mobius);

    obj->setMaterial(simple);

    MyListener listener(scene);


   auto [width, height] = eng.getWindowSize();
    
    float aspect = width / height;

    // Camera camera = PerspectiveCamera(M_PI / 3, aspect, 0.1, 100);
    scene._camera = std::make_shared<Camera>(OrthographicCamera(-5, 5, -5 * aspect, 5 * aspect, 0.1, 100));
    
    scene._object = obj;

    eng.setScene(std::make_shared<Scene>(scene));

    eng.addEventListener(std::make_shared<MyListener>(listener));

    eng.engine().run();

    return 0;
}
