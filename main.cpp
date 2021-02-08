#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cameracontrol.h"
#include "ShaderFactory.h"
#include "engine.h"

#include "GL/Texture.h"

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
    bool   onEarth = false;
public:
    ObjPtr  _cube;
    TexPtr  _skybox;
    MyListener(Scene& sc)
        : scene(sc)
    {  }

    void onRender() noexcept override
    {
    	if (onEarth) return;

        float f1 = std::abs(std::sin(1 * time));
        float f2 = std::abs(std::sin(2 * time));
        float f3 = std::abs(std::sin(3 * time));
        float f4 = time;
        float f5 = time_;

        time_ += 0.01;
        time += 0.004;
        
//        auto color = glm::vec4(1., 1., 1., 1.0);
//        auto SpecularColor = glm::vec4(1., 0., 0., 1.0);


//        _cube->getMaterial()->setAmbientColor(color);
//        _cube->getMaterial()->setDiffuseColor(color);
//        _cube->getMaterial()->setSpecularColor(SpecularColor);
//        _cube->getMaterial()->setRoughness(1);

//        _cube->setRotate(glm::vec3(0.0, 1.0, 0.0), f4);

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

    	if (glm::distance(scene.getCamera()->getPosition(), glm::vec3(earth->getWorldMat() * glm::vec4(earth->getPosition(), 1.0))) <= 0.75f) {
    		scene.setSkyBox(_skybox);
    		_cube->setEnabled(true);
    		salSys->setEnabled(false);
    		onEarth = true;
    		std::cout << "on  earth" << std::endl;
    	}
//        scene.getCamera()->setRotate(glm::vec3(1.0, 1.0, f1));

//        scene._light.setRotate(glm::vec3(1.0, 1.0, 0.0), f4);
//        (*scene.getCamera()->getChilds().begin())->setRotate(glm::vec3(1.0, 1., 1.), f4);
//        scene.setBackgroundColor(glm::vec4(f1, f2, f3, 1.0));
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

    Tex2DPtr cubicTex = std::make_shared<Texture2D>();
    Tex2DPtr titleTex = std::make_shared<Texture2D>();
    Tex2DPtr normalTex = std::make_shared<Texture2D>();
    Tex2DPtr heightTex = std::make_shared<Texture2D>();
    Tex2DPtr diffEarth = std::make_shared<Texture2D>();
    Tex2DPtr specEarth = std::make_shared<Texture2D>();
    Tex2DPtr diffSun = std::make_shared<Texture2D>();
    Tex2DPtr diffMoon = std::make_shared<Texture2D>();
    CubeMapPtr skyBox = std::make_shared<TextureCubeMap>();
    CubeMapPtr spaceSkyBox = std::make_shared<TextureCubeMap>();

    cubicTex->loadImage("resource/nicholas-andy-wood2.jpg");
    titleTex->loadImage("resource/spec.png");
    normalTex->loadImage("resource/bump_normal.png");
    heightTex->loadImage("resource/bump_depth.png");
    diffEarth->loadImage("resource/diff_earth.jpg");
    specEarth->loadImage("resource/scec_earth.jpg");
    diffSun->loadImage("resource/diff_sun.jpg");
    diffMoon->loadImage("resource/diff_moon.jpg");

    spaceSkyBox->loadImage("resource/skybox/corona_rt.png", BoxSide::SIDE_FRONT);
    spaceSkyBox->loadImage("resource/skybox/corona_lf.png", BoxSide::SIDE_BACK);
    spaceSkyBox->loadImage("resource/skybox/corona_bk.png", BoxSide::SIDE_LEFT);
    spaceSkyBox->loadImage("resource/skybox/corona_ft.png", BoxSide::SIDE_RIGHT);
    spaceSkyBox->loadImage("resource/skybox/corona_up.png", BoxSide::SIDE_TOP);
    spaceSkyBox->loadImage("resource/skybox/corona_dn.png", BoxSide::SIDE_BOTTOM);

    skyBox->loadImage("resource/skybox/posz.jpg", BoxSide::SIDE_FRONT);
    skyBox->loadImage("resource/skybox/negz.jpg", BoxSide::SIDE_BACK);
    skyBox->loadImage("resource/skybox/negx.jpg", BoxSide::SIDE_LEFT);
    skyBox->loadImage("resource/skybox/posx.jpg", BoxSide::SIDE_RIGHT);
    skyBox->loadImage("resource/skybox/posy.jpg", BoxSide::SIDE_TOP);
    skyBox->loadImage("resource/skybox/negy.jpg", BoxSide::SIDE_BOTTOM);

    scene->setSkyBox(spaceSkyBox);

    MaterialPtr simple = std::make_shared < BumpMaterial > ();

    simple->setAmbientColor(glm::vec4(0., 0., 0., 1.0));
    simple->setDiffuseColor(glm::vec4(1., 1., 1.0, 1.0));
    simple->setSpecularColor(glm::vec4(1., 1.0, 1., 1.0));
    simple->setRoughness(0.01f);

    simple->setDiffuseTexture(cubicTex);
//    simple->setSpecularTexture(titleTex);
    simple->setNormalTexture(normalTex);
    simple->setHeightTexture(heightTex);


    MaterialPtr sun = std::make_shared < PhongMaterial > ();

    sun->setAmbientColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    sun->setDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    sun->setSpecularColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    sun->setRoughness(0.3f);
    sun->setDiffuseTexture(diffSun);

    MaterialPtr earth = std::make_shared < PhongMaterial > ();

    earth->setAmbientColor(glm::vec4(0.f, 0.f, 0.f, 1.0f));
    earth->setDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    earth->setSpecularColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    earth->setRoughness(0.010f);
    earth->setDiffuseTexture(diffEarth);
    earth->setSpecularTexture(specEarth);

    MaterialPtr moon = std::make_shared < PhongMaterial > ();

    moon->setAmbientColor(glm::vec4(0.f, 0.f, 0.f, 1.0f));
    moon->setDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    moon->setSpecularColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    moon->setRoughness(0.0000001f);
    moon->setDiffuseTexture(diffMoon);

    GeometryPtr sphereGeom = std::make_shared<Sphere>(5);
//     GeometryPtr circle = std::make_shared<Circle>(10);
//     GeometryPtr rect = std::make_shared<Rect>();
//     GeometryPtr triangle = std::make_shared<Triangle>();
     GeometryPtr cube = std::make_shared<Cube>();
//     GeometryPtr cone = std::make_shared<Cone>(5);
//     GeometryPtr mobius = std::make_shared<MobiusStrip>(50);

    sunObj->setGeometry(sphereGeom);
    earthObj->setGeometry(sphereGeom);
    moonObj->setGeometry(sphereGeom);
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

    cubeObj->setPosition(glm::vec3(0.0, 0.0, 4.0));
//    cubeObj->setScale(glm::vec3(30.5, 10.5, 0.5));

//    earthObj->setPosition(glm::vec3(3.0f, 0.0f, 0.0f));
    earthObj->setScale(glm::vec3(0.5f, 0.5f, 0.5f));

    moonObj->setPosition(glm::vec3(1.0f, 0.0f, 0.0f));
    moonObj->setScale(glm::vec3(0.25f, 0.25f, 0.25f));

    NodePtr planetSystem = std::make_shared<Node>(NodeType::NODE_NODE);
    planetSystem->addChild(earthObj);
    planetSystem->addChild(moonObj);

    planetSystem->setPosition(glm::vec3(3.0f, 0.0f, 0.0f));

    NodePtr salarySystem = std::make_shared<Node>(NodeType::NODE_NODE);

    planetSystem->setEnabled(true);

    salarySystem->addChild(sunObj);
    salarySystem->addChild(planetSystem);

    salarySystem->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));

    auto [width, height] = eng.getWindowSize();
    
    float aspect = 1.0 * width / height;

    CameraPtr cam = std::make_shared<Camera>(PerspectiveCamera(M_PI / 3, aspect, 0.1, 100));

    cam->setPosition(glm::vec3(0.0, 0.0, 1.0));

//    cam->addChild(cubeObj);

    scene->setCamera(cam);

    scene->getRoot()->addChild(cubeObj);

    cubeObj->setEnabled(false);

//    (*scene->getRoot()->getChilds().begin())->addChild(cubeObj);
//    scene->getCamera()->addChild(cubeObj);

    LightPtr light = std::make_shared<Light>(LightDirectional());

    light->setColor(glm::vec4(0.0, 1.0, 1.0, 1.0));

    LightPtr headLighter = std::make_shared<Light>(LightDirectional());

    headLighter->setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));
//    headLighter->setRotate(glm::vec3(1, 1, 1));s

//    scene->getRoot()->addChild(light);

    scene->getRoot()->addChild(salarySystem);

    salarySystem->setEnabled(true);

    scene->getCamera()->addChild(headLighter);

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

    listener._cube = cubeObj;
    listener._skybox = skyBox;

    eng.addEventListener(std::make_shared<MyListener>(listener));
    eng.addEventListener(std::make_shared<CameraControl>(controler));

    eng.engine().run();

    return 0;
}
