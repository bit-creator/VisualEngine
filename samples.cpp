/*
 * samples.cpp
 *
 *  Created on: 23 ���. 2021 �.
 *      Author: IAbernikhin
 */

#include "samples.h"

#include "cameracontrol.h"
#include "ShaderFactory.h"
#include "engine.h"
#include "constants.hpp"
#include <random>

#include "GL/Texture.h"

#include "Material/GlossyMaterial.h"
#include "Material/PhongMaterial.h"
#include "Material/BumpMaterial.h"

#include "Geometry/Primitive/triangle.h"
#include "Geometry/Primitive/rect.h"
#include "Geometry/Primitive/sphere.h"
#include "Geometry/Primitive/circle.h"
#include "Geometry/Primitive/cube.h"
#include "Geometry/Primitive/cone.h"
#include "Geometry/Primitive/mobiusstrip.h"

#include <ranges>

class DemoSampleListener : public EventListener
{
    Scene& scene;

    double time = 0;
    double time_ = 0;
    bool   onEarth = false;
    float  dir = -1.0;

public:
    Entity::reference  _cube;
    TexPtr  _skybox;
    Entity::reference _atom;
    MaterialPtr _selected;
    MaterialPtr _regular;
    BumpMatPtr  _bump;
    Entity::reference  _sun;
    Entity::reference  _earth;
    Entity::reference  _moon;
    Entity::reference  _salSys;
    Entity::reference  _earthSys;

    DemoSampleListener(Scene& sc)
        : scene(sc)
    {  }

    void onRender() noexcept override {
        float f4 = time;
        float f5 = time_;

        time_ += 0.001;
        time += 0.0004;

    	if (onEarth) {

    	_bump->_scale += dir * 0.004;

	    if(_bump->_scale >= 0.2) _bump->_scale = 0.2;
	    if(_bump->_scale <= 0.) _bump->_scale = 0.0;

    		return;
    	}

//        Entity::reference salSys = *((root->getChilds()).rbegin());
//        Entity::reference sun = *((salSys->getChilds()).begin());
//
//        Entity::reference earthSys = *((salSys->getChilds()).rbegin());
//
//        Entity::reference earth = *((earthSys->getChilds()).begin());
//        Entity::reference moon = *((earthSys->getChilds()).rbegin());

        _sun->transform.setRotate(glm::vec3(0.0f, 1.0f, 0.0f), f4);
        _earth->transform.setRotate(glm::vec3(0.0f, 1.0f, 0.0f), f4);
        _moon->transform.setRotate(glm::vec3(0.0f, 1.0f, 0.0f), f5);
        _salSys->transform.setRotate(glm::vec3(0.0f, 1.0f, 0.0f), f4);
        _earthSys->transform.setRotate(glm::vec3(0.0f, 1.0f, 0.0f), f5);

        glm::mat3 indenityKernel = {
        	0, 0, 0,
			0, 1, 0,
			0, 0, 0
        };

    	if (glm::distance(scene.getCamera()->transform.getPosition(), glm::vec3(_earth->getWorldMat() * glm::vec4(_earth->transform.getPosition(), 1.0))) <= 0.75f) {
    		scene.setSkyBox(_skybox);
    		_cube->enable();
    		_atom->enable();
    		_salSys->disable();
    		Engine::engine().setPostProcesingKernel(indenityKernel);
    		onEarth = true;
    		std::cout << "on  earth" << std::endl;
    	}
    }

    void onMouseClick(int button, int action, int mode) noexcept {
    	auto& eng = Engine::engine();

    	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
    		if (auto id = eng.getPickerKey(glm::vec2(0.0, 0.0)); id) {
    			if (auto ref = scene.findObject(id); !ref.expired()) {
    				auto res = ref.get<Object3D>();
    				if(res->getMaterial() == _selected) {
    					res->setMaterial(_regular);
    				} else if (res->getMaterial() == _regular) {
    					res->setMaterial(_selected);
    				} else if(res->getMaterial() == _bump) {
    					dir *= -1;
    				}
    			}
    		}
    	}
    }

    ~DemoSampleListener() noexcept override {
    }
};

void DemoSample() {
    auto& eng = Engine::engine();

    auto scene = Scene::create();

//    Reference* ref = &refe;

//    glm::mat3 blurKernel = {
//    	1.0, 2.0, 1.0,
//    	2.0, 4.0, 2.0,
//    	1.0, 2.0, 1.0
//    };
//
//    blurKernel /= 16;
//
    glm::mat3 indenityKernel = {
    	0, 0, 0,
		0, 1, 0,
		0, 0, 0
    };

    eng.setPostProcesingKernel(indenityKernel);

    eng.setScene(scene);

    auto [width, height] = eng.getWindowSize();
    float aspect = 1.0 * width / height;

    auto cam = Camera::create(PerspectiveCamera(PI / 3, aspect, 0.1, 100));
    auto headLighter = Light::create(cam);

//    std::cout << scene->getCamera()->getChilds().size() << std::endl;

    auto controler = CameraControl::create(cam);
    eng.addEventListener(controler);

//    cam->addChild(headLighter);

//    scene->root()->addChild(cam);

//    scene->setCamera(cam);

    auto sphereGeom = Sphere::create(5);
    auto cube = Cube::create();

    auto cubicTex    = Texture2D::create("resource/nicholas-andy-wood2.jpg");
    auto titleTex    = Texture2D::create("resource/spec.png");
    auto normalTex   = Texture2D::create("resource/bump_normal.png");
    auto heightTex   = Texture2D::create("resource/bump_depth.png");
    auto diffEarth   = Texture2D::create("resource/diff_earth.jpg");
    auto specEarth   = Texture2D::create("resource/scec_earth.jpg");
    auto diffSun     = Texture2D::create("resource/diff_sun.jpg");
    auto diffMoon    = Texture2D::create("resource/diff_moon.jpg");
    auto skyBox      = TextureCubeMap::create();
    auto spaceSkyBox = TextureCubeMap::create();

    auto simple   = std::make_shared<BumpMaterial>();
    auto glossy   = GlossyMaterial::create();
	auto selected = GlossyMaterial::create();
    auto sun      = PhongMaterial::create();
    auto earth    = PhongMaterial::create();
    auto moon     = PhongMaterial::create();

    auto cubeObj  = Object3D::create();
    auto salarySystem = Node::create();
    auto planetSystem = Node::create(salarySystem);
    auto atom 		  = Node::create();

//    auto sunObj   = Object3D::create(sun, sphereGeom);
//    auto earthObj = Object3D::create(earth, sphereGeom);
//    auto moonObj  = Object3D::create(moon, sphereGeom);
//    auto cubeObj  = Object3D::create(simple, cube);

    auto sunObj   = Object3D::create(salarySystem);
    auto earthObj = Object3D::create(planetSystem);
    auto moonObj  = Object3D::create(planetSystem);

	sunObj.get<Object3D>()->initialize(sun, sphereGeom);
    earthObj.get<Object3D>()->initialize(earth, sphereGeom);
    moonObj.get<Object3D>()->initialize(moon, sphereGeom);
    cubeObj.get<Object3D>()->initialize(simple, cube);

//	dynamic_cast<Object3D*>(sunObj.get())->setClicable(true);
//	dynamic_cast<Object3D*>(moonObj.get())->setClicable(true);
//	dynamic_cast<Object3D*>(earthObj.get())->setClicable(true);
//	dynamic_cast<Object3D*>(cubeObj.get())->setClicable(true);

	sunObj.get<Object3D>()->setClicable(true);
	moonObj.get<Object3D>()->setClicable(true);
	earthObj.get<Object3D>()->setClicable(true);
	cubeObj.get<Object3D>()->setClicable(true);

    std::vector<Entity::reference> electrons;

    for(int i = 0; i< 10; ++i) {
    	auto el = Object3D::create(atom);
    	el.get<Object3D>()->initialize(glossy, sphereGeom);

    	electrons.push_back(el);
    	el.get<Object3D>()->setClicable(true);
    	atom->addChild(el);
    }

    scene->setSkyBox(spaceSkyBox);

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


    headLighter.get<Light>()->setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));


    simple->setAmbientColor(glm::vec4(0., 0., 0., 1.0));
    simple->setDiffuseColor(glm::vec4(1., 1., 1.0, 1.0));
    simple->setSpecularColor(glm::vec4(1., 1.0, 1., 1.0));
    simple->setRoughness(0.01f);

    simple->setDiffuseTexture(cubicTex);
    simple->setNormalTexture(normalTex);
    simple->setHeightTexture(heightTex);


    glossy->setColor(glm::vec4(1.0, 1.0, 1., 1.0));
    glossy->set1RefInd(1.0f);
    glossy->set2RefInd(1.52f);
    glossy->setRoughness(0.3f);


    selected->setColor(glm::vec4(0.5, 0.5, 1., 1.0));
    selected->set1RefInd(1.0f);
    selected->set2RefInd(1.52f);
    selected->setRoughness(0.3f);


    sun->setAmbientColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    sun->setDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    sun->setSpecularColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    sun->setRoughness(0.3f);

    sun->setDiffuseTexture(diffSun);


    earth->setAmbientColor(glm::vec4(0.f, 0.f, 0.f, 1.0f));
    earth->setDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    earth->setSpecularColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    earth->setRoughness(0.010f);

    earth->setDiffuseTexture(diffEarth);
    earth->setSpecularTexture(specEarth);


    moon->setAmbientColor(glm::vec4(0.f, 0.f, 0.f, 1.0f));
    moon->setDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    moon->setSpecularColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    moon->setRoughness(0.0000001f);

    moon->setDiffuseTexture(diffMoon);

    float angle = 2 * PI / electrons.size();
    auto index = 0;
    float radius = 5.0;

    for(auto electron : electrons) {
    	auto currentAngle = index * angle;
//    	electron->setGeometry(sphereGeom);
    	electron->transform.setPosition(glm::vec3(radius* cos(currentAngle), 0, radius * sin(currentAngle)));
//    	atom->addChild(electron);
    	++index;
    }

    atom->disable();
    planetSystem->enable();
    cubeObj->disable();
    salarySystem->enable();

    cubeObj->transform.setPosition(glm::vec3(0.0, 0.0, 4.0));
//    cubeObj->setScale(glm::vec3(1.0, 1.0, 50.0));
    atom->transform.setPosition(cubeObj->transform.getPosition());
    moonObj->transform.setPosition(glm::vec3(1.0f, 0.0f, 0.0f));
    planetSystem->transform.setPosition(glm::vec3(3.0f, 0.0f, 0.0f));
    salarySystem->transform.setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    cam->transform.setPosition(glm::vec3(0.0, 0.0, 1.0));

    atom->transform.setScale(glm::vec3(0.7));
    earthObj->transform.setScale(glm::vec3(0.5f, 0.5f, 0.5f));
    moonObj->transform.setScale(glm::vec3(0.25f, 0.25f, 0.25f));

//    planetSystem->addChild(earthObj);
//    planetSystem->addChild(moonObj);
//
//    salarySystem->addChild(sunObj);
//    salarySystem->addChild(planetSystem);
//
//    scene->root()->addChild(cubeObj);
//    scene->root()->addChild(atom);
//    scene->root()->addChild(salarySystem);

    DemoSampleListener listener(*scene);

    listener._cube = cubeObj;
    listener._sun  = sunObj;
    listener._moon = moonObj;
    listener._earth = earthObj;
    listener._salSys = salarySystem;
    listener._earthSys = planetSystem;


    listener._skybox = skyBox;
    listener._atom = atom;
    listener._selected = selected;
    listener._regular = glossy;
    listener._bump = simple;

    eng.addEventListener(std::make_shared<DemoSampleListener>(listener));
}


glm::vec3 random(int a, int b) {
    std::random_device rd{};
    std::mt19937 gen{rd()};

	std::normal_distribution<> normal_dist(a, b);

	return { normal_dist(gen), normal_dist(gen), normal_dist(gen) };
}


using std::ranges::views::iota;

void sphereSample() {
    auto& eng = Engine::engine();

    auto scene = Scene::create();

    eng.setScene(scene);

    glm::mat3 indenityKernel = {
    	0, 0, 0,
		0, 1, 0,
		0, 0, 0
    };

    eng.setPostProcesingKernel(indenityKernel);

    auto [width, height] = eng.getWindowSize();
    float aspect = 1.0 * width / height;

//    auto lighter = Light::create();
//    lighter.get<Light>()->transform.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

    auto cam = Camera::create(PerspectiveCamera(PI / 3, aspect, 0.1, 100));

    cam.get<Camera>()->transform.setPosition(glm::vec3(0.0, 0.0, 0.0));

    auto controler = CameraControl::create(cam);
    eng.addEventListener(controler);

//    scene->setCamera(cam);

    auto geom = Cube::create();
    auto sphereg = Sphere::create(5);

    auto tex = Texture2D::create("resource/nicholas-andy-wood2.jpg");
    auto normalTex   = Texture2D::create("resource/bump_normal.png");
    auto heightTex   = Texture2D::create("resource/bump_depth.png");

    auto bubleMat = PhongMaterial::create();

//    bubleMat->setAmbientColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
    bubleMat->setSpecularColor(glm::vec4(0., 0.0, 0., 1.0));
    bubleMat->setRoughness(0.0f);

    auto mat = std::make_shared<BumpMaterial>();

    auto spaceSkyBox = TextureCubeMap::create();
    auto headLighter = Light::create();
    auto pointLighter = Light::create();
    auto spotLighter = Light::create();

    headLighter.get<Light>()->setupDir(glm::vec4(1.0, 0.0, 0.0, 1.0));
    pointLighter.get<Light>()->setupPoint(100, glm::vec4(0.0, 1.0, 0.0, 1.0));

    bubleMat->setDiffuseColor(pointLighter.get<Light>()->getColor());

    auto pointBubl = Object3D::create(pointLighter);
    pointBubl->transform.setPosition(pointLighter.get<Light>()->transform.getPosition());
    pointBubl->transform.setScale(glm::vec3(0.1, 0.1, 0.1));
    pointBubl.get<Object3D>()->initialize(bubleMat, sphereg, false);
    pointBubl->enable();

    spotLighter.get<Light>()->setupSpot(100, 0.5, glm::vec4(0.0, 0.0, 1.0, 1.0));

    spaceSkyBox->loadImage("resource/skybox/corona_rt.png", BoxSide::SIDE_FRONT);
    spaceSkyBox->loadImage("resource/skybox/corona_lf.png", BoxSide::SIDE_BACK);
    spaceSkyBox->loadImage("resource/skybox/corona_bk.png", BoxSide::SIDE_LEFT);
    spaceSkyBox->loadImage("resource/skybox/corona_ft.png", BoxSide::SIDE_RIGHT);
    spaceSkyBox->loadImage("resource/skybox/corona_up.png", BoxSide::SIDE_TOP);
    spaceSkyBox->loadImage("resource/skybox/corona_dn.png", BoxSide::SIDE_BOTTOM);

    scene->setSkyBox(spaceSkyBox);

    mat->setDiffuseTexture(tex);

    mat->setAmbientColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
    mat->setDiffuseColor(glm::vec4(0.5, 0.5, 0.5, 1.0));
    mat->setSpecularColor(glm::vec4(1., 1.0, 1., 1.0));
    mat->setRoughness(0.01f);


    mat->setNormalTexture(normalTex);
    mat->setHeightTexture(heightTex);

    for(int i = 0; i < 99; i ++) {
    auto obj = Object3D::create();
    obj->transform.setPosition(random(0, 10));
    obj.get<Object3D>()->initialize(mat, geom, true);
    obj->enable();
    }

//    for(int i = 0; i < 50; i ++) {
//    auto light = Light::create();
//    light->transform.setPosition(random(0, 10));
//    light.get<Light>()->setColor(random(0.5, 1));
//    light->enable();
//    }
}
