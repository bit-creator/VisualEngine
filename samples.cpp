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

class DemoSampleListener : public EventListener
{
    Scene& scene;

    double time = 0;
    double time_ = 0;
    bool   onEarth = false;
    float  dir = -1.0;

public:
    ObjPtr  _cube;
    TexPtr  _skybox;
    NodePtr _atom;
    MaterialPtr _selected;
    MaterialPtr _regular;
    BumpMatPtr  _bump;

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

        glm::mat3 indenityKernel = {
        	0, 0, 0,
			0, 1, 0,
			0, 0, 0
        };

    	if (glm::distance(scene.getCamera()->getPosition(), glm::vec3(earth->getWorldMat() * glm::vec4(earth->getPosition(), 1.0))) <= 0.75f) {
    		scene.setSkyBox(_skybox);
    		_cube->setEnabled(true);
    		_atom->setEnabled(true);
    		salSys->setEnabled(false);
    		Engine::engine().setPostProcesingKernel(indenityKernel);
    		onEarth = true;
    		std::cout << "on  earth" << std::endl;
    	}
    }

    void onMouseClick(int button, int action, int mode) noexcept {
//    	auto& eng = Engine::engine();

    	std::cout <<  Engine::engine().getPickerKey() << std::endl;





//    	auto res = scene.getRoot()->rayCast(scene.getCamera()->getRay(glm::vec2(0.0, 0.0)));
//    	if (res.empty()) {
//    		std::cout << "no object" << std::endl;
//    	} else {
//    		Intersection* el = &(res.front());
//    		for (auto elem : res) if(elem._distance <= el->_distance) el = &elem;
//    			if(el->_obj->getMaterial() == _selected) {
//    				el->_obj->setMaterial(_regular);
//    			} else if (el->_obj->getMaterial() == _regular) {
//    				el->_obj->setMaterial(_selected);
//    			} else if(el->_obj->getMaterial() == _bump) {
//    		    	dir *= -1;
//    			}
//    	}
    }

    ~DemoSampleListener() noexcept override {
    }
};

void DemoSample() {
    auto& eng = Engine::engine();

    auto scene = Scene::create();

    glm::mat3 blurKernel = {
    	1.0, 2.0, 1.0,
    	2.0, 4.0, 2.0,
    	1.0, 2.0, 1.0
    };

    blurKernel /= 16;

    eng.setPostProcesingKernel(blurKernel);

    eng.setScene(scene);

    auto [width, height] = eng.getWindowSize();
    float aspect = 1.0 * width / height;

    auto headLighter = Light::createSharedThisPtr(LightDirectional());
    auto cam = Camera::createSharedThisPtr(PerspectiveCamera(PI / 3, aspect, 0.1, 100));

    auto controler = CameraControl::create(cam);
    eng.addEventListener(controler);

    cam->addChild(headLighter);

    scene->setCamera(cam);

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

    auto atom 		  = Node::create();
    auto planetSystem = Node::create();
    auto salarySystem = Node::create();

    auto sunObj   = Object3D::createSharedThisPtr(sun);
    auto earthObj = Object3D::createSharedThisPtr(earth);
    auto moonObj  = Object3D::createSharedThisPtr(moon);
    auto cubeObj  = Object3D::createSharedThisPtr(simple);

    std::vector<ObjPtr> electrons{10, ObjPtr()};
    for(auto& el : electrons){
    	el = Object3D::createSharedThisPtr(glossy);
    }

    sunObj->setGeometry(sphereGeom);
    earthObj->setGeometry(sphereGeom);
    moonObj->setGeometry(sphereGeom);
    cubeObj->setGeometry(cube);

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


    headLighter->setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));


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
    	electron->setGeometry(sphereGeom);
    	electron->setPosition(glm::vec3(radius* cos(currentAngle), 0, radius * sin(currentAngle)));
    	atom->addChild(electron);
    	++index;
    }

    atom->setEnabled(false);
    planetSystem->setEnabled(true);
    cubeObj->setEnabled(false);
    salarySystem->setEnabled(true);

    cubeObj->setPosition(glm::vec3(0.0, 0.0, 4.0));
    atom->setPosition(cubeObj->getPosition());
    moonObj->setPosition(glm::vec3(1.0f, 0.0f, 0.0f));
    planetSystem->setPosition(glm::vec3(3.0f, 0.0f, 0.0f));
    salarySystem->setPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    cam->setPosition(glm::vec3(0.0, 0.0, 1.0));

    atom->setScale(glm::vec3(0.7));
    earthObj->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
    moonObj->setScale(glm::vec3(0.25f, 0.25f, 0.25f));

    planetSystem->addChild(earthObj);
    planetSystem->addChild(moonObj);

    salarySystem->addChild(sunObj);
    salarySystem->addChild(planetSystem);

    scene->getRoot()->addChild(cubeObj);
    scene->getRoot()->addChild(atom);
    scene->getRoot()->addChild(salarySystem);

    DemoSampleListener listener(*scene);

    listener._cube = cubeObj;
    listener._skybox = skyBox;
    listener._atom = atom;
    listener._selected = selected;
    listener._regular = glossy;
    listener._bump = simple;

    eng.addEventListener(std::make_shared<DemoSampleListener>(listener));
}

