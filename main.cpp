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

public:
    ObjPtr  _cube;
    MyListener(Scene& sc)
        : scene(sc)
    {  }

    void onRender() noexcept override
    {

        float f1 = std::abs(std::sin(1 * time));
        float f2 = std::abs(std::sin(2 * time));
        float f3 = std::abs(std::sin(3 * time));
        float f4 = time;
        float f5 = time_;

        time_ += 0.01;
        time += 0.001;
        
        auto color = glm::vec4(0.1, 0.1, 0.1, 1.0);
        auto SpecularColor = glm::vec4(1., 0., 0., 1.0);

        _cube->getMaterial()->setAmbientColor(color);
        _cube->getMaterial()->setDiffuseColor(color);
        _cube->getMaterial()->setSpecularColor(SpecularColor);
        _cube->getMaterial()->setRoughness(1);

//        _cube->setRotate(glm::vec3(1.0, 1.0, 0.0), f4);

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

        scene.getCamera()->setRotate(glm::vec3(1.0, 1.0, f1));

//        scene._light.setRotate(glm::vec3(1.0, 1.0, 0.0), f4);
//        (*scene.getCamera()->getChilds().begin())->setRotate(glm::vec3(1.0, 1., 1.), f4);
//        scene.setBackgroundColor(glm::vec4(f1, f2, f3, 1.0));
    }

    void onMouseClick(int button, int action, int mode) noexcept {
    	auto res = scene.getRoot()->rayCast(scene.getCamera()->getRay(glm::vec2(0.0, 0.0)));
    	if (res.empty()) {
    		std::cout << "no object" << std::endl;
    	} else {
    		for(auto& el : res)
    		el._obj->getMaterial()->setAmbientColor(glm::vec4(rand() * 1.0f / RAND_MAX, rand() * 1.0f / RAND_MAX, rand() * 1.0f / RAND_MAX, 1.0));
    	}
//    	std::cout << "click" << std::endl;
    }

    ~MyListener() noexcept override {
    }

};

int main()
{
	/**
	 * Вместо этого мы сделаем простой пикер основаный на тесте луча
	 * Для этого у ноды создадим метод
	 *
	 * RayCast(ray: Ray)
	 *
	 * Давай наверное возвратим список всех пересечений.
	 *
	 * Т.е. RayCast(ray: Ray): Nodes[]
	 *
	 * Не пугайся - это тайпскриптовый синтаксис)
	 * Метод должен рекурсивно пройти по всем нодам наследникам
	 * и проверить пересечение с геометрией с учётом трансформации
	 * Т.е. если нода типа объект, то сделать
	 *
	 * rayCast(ray: Ray);
	 *
	 * для геометрии предварительно применив к лучу мировое преобразование
	 * Т.е. нам не нужно выполнять преобразование для каждой вершины, мы ж можем преобразовать луч.
	 * Пока начнём с простого - сферу и куб пересечём аналитически
	 * Т.е. мы ж знаем, что они единичные и никому не позволяем править вершины.
	 * Значит по формуле можно сразу узнать пересечение.
	 * Итак, нам нужен маленький класс
	 *
	 * Ray {
   	 *  	   vec3 origin;
   	 *  	   vec3 dir;
	 *  }
	 *
	 * В системе координат камеры луч выходит из нуля координат,
	 * т.е. очевидно в мировых координтах это просто положение камеры
	 * С направлением чуть сложнее. Будем считать, что камера перспективная.
	 * Для начала найдём координаты мышки в каноническом объёме
	 *
	 * 		mouse.x = ( clientX / window.Width ) * 2 - 1;
	 * 		mouse.y = - (clientY / window.Height ) * 2 + 1;
	 *
	 * Тогда мировое положение точки на передней стенке канонического объёма
	 *
	 *		inv(viewProj) * (mouse.x, mouse.y, -1, 1)
	 *
	 * Ну а направление - разница.
	 * Но поскольку у нас мышка всегда по центру, то можно и упростить
	 * Я думаю будет лучше создать структуру
	 *
	 * Intersection {
 	 *		 distance – distance between the origin of the ray and the intersection
	 * 		 point – point of intersection, in world coordinates
	 * 		 object – the intersected object
	 * }
	 *
	 * И возвращать массив таких структур
	 * Итак. У класса геометрии появляется метод
	 *
	 * rayCast(ray: Ray): distance.
	 *
	 * Если отрицательное число, то пересечени нету.
	 * У ноды сцены рекурсивный
	 *
	 * rayCast(ray: Ray): Intersection[]
	 *
	 * У камеры можно метод
	 *
	 * getRay(mouseX, mouseY): Ray
	 *
	 * Для сферы и куба rayCast нужно перегрузить и аналитически посчитать перечечение
	 * В общем случае - пройти по всем треугольникам по массиву индексов
	 *  и проверить пересечение луча и треугольника.
	 * Но для этого нужно иметь эти массивы.
	 * Пока не имплементь это
	 */

    auto& eng = Engine::engine();

    ScenePtr scene = std::make_shared<Scene>();

    auto sunObj = std::make_shared<Object3D>();
    auto earthObj = std::make_shared<Object3D>();
    auto moonObj = std::make_shared<Object3D>();
    auto cubeObj = std::make_shared<Object3D>();

    Tex2DPtr cubicTex = std::make_shared<Texture2D>();
    Tex2DPtr titleTex = std::make_shared<Texture2D>();
    Tex2DPtr diffEarth = std::make_shared<Texture2D>();
    Tex2DPtr specEarth = std::make_shared<Texture2D>();
    Tex2DPtr diffSun = std::make_shared<Texture2D>();
    Tex2DPtr diffMoon = std::make_shared<Texture2D>();

    cubicTex->loadImage("resource/cube.jpg");
    titleTex->loadImage("resource/spec.png");
    diffEarth->loadImage("resource/diff_earth.jpg");
    specEarth->loadImage("resource/scec_earth.jpg");
    diffSun->loadImage("resource/diff_sun.jpg");
    diffMoon->loadImage("resource/diff_moon.jpg");
    
    MaterialPtr simple = std::make_shared < Material > ();

    simple->setAmbientColor(glm::vec4(0., 0., 0., 1.0));
    simple->setDiffuseColor(glm::vec4(1., 0.2, 0.2, 1.0));
    simple->setSpecularColor(glm::vec4(1., 1., 1., 1.0));
    simple->setRoughness(0.001f);

    simple->setDiffuseTexture(cubicTex);
    simple->setSpecularTexture(titleTex);

    MaterialPtr sun = std::make_shared < Material > ();

    sun->setAmbientColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
//    sun->setDiffuseColor(glm::vec4(1.0f, 0.5f, 0.0f, 1.0f));
//    sun->setSpecularColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    sun->setRoughness(0.3f);
    sun->setDiffuseTexture(diffSun);

    MaterialPtr earth = std::make_shared < Material > ();

    earth->setAmbientColor(glm::vec4(0.f, 0.f, 0.f, 1.0f));
//    earth->setDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
//    earth->setSpecularColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    earth->setRoughness(0.010f);
    earth->setDiffuseTexture(diffEarth);
    earth->setSpecularTexture(specEarth);

    MaterialPtr moon = std::make_shared < Material > ();

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

    cam->setPosition(glm::vec3(0.0, 0.0, -1.0));

//    cam->addChild(cubeObj);

    scene->setCamera(cam);

    scene->getRoot()->addChild(cubeObj);



//    (*scene->getRoot()->getChilds().begin())->addChild(cubeObj);
//    scene->getCamera()->addChild(cubeObj);

    LightPtr light = std::make_shared<Light>(LightDirectional());

    light->setColor(glm::vec4(0.0, 1.0, 1.0, 1.0));

    LightPtr headLighter = std::make_shared<Light>(LightDirectional());

    headLighter->setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

//    scene->getRoot()->addChild(light);

    scene->getRoot()->addChild(salarySystem);

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

    eng.addEventListener(std::make_shared<MyListener>(listener));
    eng.addEventListener(std::make_shared<CameraControl>(controler));

    eng.engine().run();

    return 0;
}
