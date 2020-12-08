#include <iostream>
#include <cmath>
#include <cstdlib>

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
    double time = 0;
    double time_ = 0;

public:

    MyListener(Scene& sc)
        : scene(sc)
    {  }

    void onRender() noexcept override
    {

        float f1 = std::abs(std::sin(1 * time));
//        float f2 = std::abs(std::sin(2 * time));
//        float f3 = std::abs(std::sin(3 * time));
        float f4 = time;
        float f5 = time_;

        time_ += 0.1;
        time += 0.01;
        
//        auto color = glm::vec4(1., 0.2, 0.2, 1.0);
//        auto SpecularColor = glm::vec4(1., 1., 1., 1.0);

//        const auto& material = scene._objects[0]->getMaterial();
//
//        material -> setColor(ColorTarget::Ambient, color);
//        material -> setColor(ColorTarget::Diffuse, color);
//        material -> setColor(ColorTarget::Specular, SpecularColor);
//        material -> setRoughness(0.001);
//        material -> setPolygonsFillMode(GL_FILL);
//        scene._objects[0]->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
//        scene._objects[0]->setPosition(glm::vec3(0.0, 0.0, 10.0));
//
//        scene._objects[0]->setRotate(glm::vec3(1., 1., 1.), f4);

//         scene._object->setRotate(glm::vec3(1., 1., 1.), 0.0);
//         scene._object->setScale(glm::vec3(1.f, 1.0f, 1.f));

        NodePtr root = scene.getRoot();

        NodePtr salSys = *((root->getChilds()).rbegin());
        NodePtr sun = *((salSys->getChilds()).begin());

        NodePtr earthSys = *((salSys->getChilds()).rbegin());

        NodePtr earth = *((earthSys->getChilds()).begin());
        NodePtr moon = *((earthSys->getChilds()).rbegin());

        sun->setRotate(glm::vec3(0.0f, 1.0f, 0.0f), f4);
        earth->setRotate(glm::vec3(0.0f, 1.0f, 0.0f), f4);
        moon->setRotate(glm::vec3(0.0f, 1.0f, 0.0f), f5);
        salSys->setRotate(glm::vec3(0.0f, 1.0f, 0.0f), f4);
        earthSys->setRotate(glm::vec3(0.0f, 1.0f, 0.0f), f5);

//        scene.getCamera()->setPosition(glm::vec3(0.0, 0.0, f1));
//        (*scene.getCamera()->getChilds().begin())->setRotate(glm::vec3(1.0, 1., 1.), f4);
    }

    ~MyListener() noexcept override {
    }

};

int main()
{
    auto& eng = Engine::engine();

    ScenePtr scene = std::make_shared<Scene>();

    auto sunObj = std::make_shared<Object3D>();
    auto earthObj = std::make_shared<Object3D>();
    auto moonObj = std::make_shared<Object3D>();
    auto cubeObj = std::make_shared<Object3D>();

    
    MaterialPtr simple = std::make_shared < Material > ();

    simple->setColor(ColorTarget::Ambient, glm::vec4(1., 0.2, 0.2, 1.0));
    simple->setColor(ColorTarget::Diffuse, glm::vec4(1., 0.2, 0.2, 1.0));
    simple->setColor(ColorTarget::Specular, glm::vec4(1., 1., 1., 1.0));
    simple->setRoughness(0.001f);

    MaterialPtr sun = std::make_shared < Material > ();

    sun->setColor(ColorTarget::Ambient, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    sun->setColor(ColorTarget::Diffuse, glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
    sun->setColor(ColorTarget::Specular, glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    sun->setRoughness(0.3f);

    MaterialPtr earth = std::make_shared < Material > ();

    earth->setColor(ColorTarget::Ambient, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
    earth->setColor(ColorTarget::Diffuse, glm::vec4(0.1f, 0.6f, 1.0f, 1.0f));
    earth->setColor(ColorTarget::Specular, glm::vec4(0.2f, 0.4f, 0.0f, 1.0f));
    earth->setRoughness(0.1f);

    MaterialPtr moon = std::make_shared < Material > ();

    moon->setColor(ColorTarget::Ambient, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    moon->setColor(ColorTarget::Diffuse, glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
    moon->setColor(ColorTarget::Specular, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    moon->setRoughness(0.01f);
        
    GeometryPtr sunGeom = std::make_shared<Sphere>(5);
    GeometryPtr earthGeom = std::make_shared<Sphere>(5);
    GeometryPtr moonGeom = std::make_shared<Sphere>(5);
//     GeometryPtr circle = std::make_shared<Circle>(10);
//     GeometryPtr rect = std::make_shared<Rect>();
//     GeometryPtr triangle = std::make_shared<Triangle>();
     GeometryPtr cube = std::make_shared<Cube>();
//     GeometryPtr cone = std::make_shared<Cone>(5);
//     GeometryPtr mobius = std::make_shared<MobiusStrip>(50);

    sunObj->setGeometry(sunGeom);
    earthObj->setGeometry(earthGeom);
    moonObj->setGeometry(moonGeom);
    cubeObj->setGeometry(cube);

//     obj.setGeometry(circle);
//     obj.setGeometry(rect);
//     obj1->setGeometry(cube);
//     obj3->setGeometry(cone);
//     obj.setGeometry(mobius);

    sunObj->setMaterial(sun);
    earthObj->setMaterial(earth);
    moonObj->setMaterial(moon);
    cubeObj->setMaterial(simple);

    cubeObj->setPosition(glm::vec3(0.0, 0.0, 5.0));
    cubeObj->setScale(glm::vec3(0.5, 0.5, 0.5));

//    earthObj->setPosition(glm::vec3(3.0f, 0.0f, 0.0f));
    earthObj->setScale(glm::vec3(0.5f, 0.5f, 0.5f));

    moonObj->setPosition(glm::vec3(1.0f, 0.0f, 0.0f));
    moonObj->setScale(glm::vec3(0.25f, 0.25f, 0.25f));

    NodePtr planetSystem = std::make_shared<Node>(NodeType::NODE_NODE);
    planetSystem->addChild(earthObj);
    planetSystem->addChild(moonObj);

    planetSystem->setPosition(glm::vec3(3.0f, 0.0f, 0.0f));

    NodePtr salarySystem = std::make_shared<Node>(NodeType::NODE_NODE);

    salarySystem->addChild(sunObj);
    salarySystem->addChild(planetSystem);

    salarySystem->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

    auto [width, height] = eng.getWindowSize();
    
    float aspect = 1.0 * width / height;

    CameraPtr cam = std::make_shared<Camera>(PerspectiveCamera(M_PI / 3, aspect, 0.1, 100));

    cam->setPosition(glm::vec3(0.0, 0.0, -5.0));

    cam->addChild(cubeObj);

    scene->setCamera(cam);

//    (*scene->getRoot()->getChilds().begin())->addChild(cubeObj);
//    scene->getCamera()->addChild(cubeObj);

    scene->getRoot()->addChild(salarySystem);


    // scene._camera = std::make_shared<Camera>(OrthographicCamera(-5, 5, -5 * aspect, 5 * aspect, 0.1, 100));

//	float scale = (rand() % 25 + 25) / 100;
//	float pos1 = rand() % 20 - 10;
//	float pos2 = rand() % 20 - 10;
//	float pos3 = rand() % 20 - 10;

//	obj2->setMaterial(simple);
//	obj2->setPosition(glm::vec3(1.0, 1.0, 8.0));
//	obj2->setScale(glm::vec3(0.5, 1., 1.0));

//	scene._objects.push_back(obj2);

//	obj3->setMaterial(simple);
//	obj3->setPosition(glm::vec3(0.0, 0.0, 5.0));
//	obj3->setScale(glm::vec3(1., 0.5, 1.0));

//	scene._objects.push_back(obj3);

//    srand(time(nullptr));
//
//    for(int i = 1; i <= 10; ++i)
//    {
//    	auto newObj = std::make_shared<Object3D>(*obj2);
//
//    	float scale = (1.0)*(rand() % 25 + 25) / 100;
//    	float pos1 = rand() % 20 - 10;
//    	float pos2 = rand() % 20 - 10;
//    	float pos3 = rand() % 20 - 10;
//
//    	newObj->setMaterial(simple);
//    	newObj->setPosition(glm::vec3(pos1, pos2, pos3));
//    	newObj->setScale(glm::vec3(scale, scale, scale));
//
//    	scene._objects.push_back(newObj);
//    }



    eng.setScene(scene);

    MyListener listener(*scene);
    CameraControl controler(scene->getCamera());

    eng.addEventListener(std::make_shared<MyListener>(listener));
    eng.addEventListener(std::make_shared<CameraControl>(controler));

    eng.engine().run();

    return 0;
}
