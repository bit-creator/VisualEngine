#include <iostream>
#include <cmath>

#include "cameracontrol.h"
#include "engine.h"

#include "Primitive/triangle.h"
#include "Primitive/rect.h"
#include "Primitive/sphere.h"
#include "Primitive/circle.h"
#include "Primitive/cube.h"
#include "Primitive/cone.h"
#include "Primitive/mobiusstrip.h"

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

        float f1 = std::abs(std::sin(1 * time));
        float f2 = std::abs(std::sin(2 * time));
        float f3 = std::abs(std::sin(3 * time));
        float f4 = time;

        time += 0.01;
        
        auto color = glm::vec4(1., 0.2, 0.2, 1.0);
        auto SpecularColor = glm::vec4(1., 1., 1., 1.0);

        const auto& material = scene._object->getMaterial();
        
        material -> setColor(ColorTarget::Ambient, color);
        material -> setColor(ColorTarget::Diffuse, color);
        material -> setColor(ColorTarget::Specular, SpecularColor);
        material -> setRoughness(0.01);
        material -> setPolygonsFillMode(GL_FILL);
        scene._object->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
        scene._object->setPosition(glm::vec3(0.0, 0.0, 3.0));

//        scene._object->setRotate(glm::vec3(1., 1., 1.), f4);
//         scene._object->setRotate(glm::vec3(1., 1., 1.), 0.0);
//         scene._object->setScale(glm::vec3(1.f, 1.0f, 1.f));
    }

    ~MyListener() noexcept override {
    }

};

int main()
{
    auto& eng = Engine::engine();

    Scene scene;

    auto obj = std::make_shared<Object3D>();
    
    MaterialPtr simple = std::make_shared < Material > ();
        
    GeometryPtr sphere = std::make_shared<Sphere>(5);
//     GeometryPtr circle = std::make_shared<Circle>(10);
//     GeometryPtr rect = std::make_shared<Rect>();
//     GeometryPtr triangle = std::make_shared<Triangle>();
//     GeometryPtr cube = std::make_shared<Cube>();
//     GeometryPtr cone = std::make_shared<Cone>(5);
//     GeometryPtr mobius = std::make_shared<MobiusStrip>(50);

    obj->setGeometry(sphere);
//     obj.setGeometry(circle);
//     obj.setGeometry(rect);
//     obj->setGeometry(cube);
//     obj.setGeometry(cone);
//     obj.setGeometry(mobius);

    obj->setMaterial(simple);


    auto [width, height] = eng.getWindowSize();
    
    float aspect = 1.0 * width / height;

    scene._camera = std::make_shared<Camera>(PerspectiveCamera(M_PI / 3, aspect, 0.1, 100));
    // scene._camera = std::make_shared<Camera>(OrthographicCamera(-5, 5, -5 * aspect, 5 * aspect, 0.1, 100));
    
    scene._object = obj;

    eng.setScene(std::make_shared<Scene>(scene));

    MyListener listener(scene);
    CameraControl controler(scene._camera);

    eng.addEventListener(std::make_shared<MyListener>(listener));
    eng.addEventListener(std::make_shared<CameraControl>(controler));

    eng.engine().run();

    return 0;
}
