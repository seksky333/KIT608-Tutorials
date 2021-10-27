#include "Exam3d.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include "Component.h"
#include "Transform.h"
#include "GLRenderer.h"
#include "KeyboardController.h"
#include "Input.h"
#include "Math.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Cylinder.h"
#include "Lamp.h"
#include "AnimationTutorial.h"
#include "AnimationTest.h"
#include "LookAtBehaviour.h"
#include "LampBehaviour.h"
#include "Animation.h"
#include "Sphere.h"
#include "Tablet.h"
#include "WineGlass.h"
#include "TableWithGlass.h"
#include "Robot.h"
#include "Plate.h"
#include "House.h"
#include "BrokenRobot.h"
#include "RobotHand.h"
#include "Terrain.h"
#include "SoundTestTask.h"
#include "Billboard.h"
#include "BillboardTask.h"
#include "Robot1Task.h"
#include "Robot2Task.h"
#include "CameraTask.h"
#include "WineGlassTask.h"


using namespace T3D;
namespace T3D
{
    const float legJPosX = 0.0;
    const float legJPosY = -0.1425;
    const float legJPosZ = 0.10;

    bool Exam3d::init() {
        WinGLApplication::init();

        //light to the scene
        GameObject* lightObj = new GameObject(this);
        Light* light = new Light(Light::Type::DIRECTIONAL);
        light->setAmbient(.3, .3, .3);
        light->setDiffuse(1, 1, 1);
        light->setSpecular(1, 1, 1);
        lightObj->setLight(light);
        lightObj->getTransform()->
            setLocalRotation(
                Vector3(-45 * Math::DEG2RAD, 70 * Math::DEG2RAD, 0));
        lightObj->getTransform()->setParent(root);


        //material
        Material* green =
            renderer->createMaterial(Renderer::PR_OPAQUE);
        green->setDiffuse(0, 1, 0, 1);

        Material* grey = renderer->createMaterial(Renderer::PR_OPAQUE);
        grey->setDiffuse(0.8, 0.8, 0.9, 1);

        Material* blue = renderer->createMaterial(Renderer::PR_OPAQUE);
        blue->setDiffuse(0, 0, 1, 1);

        //camera
        //add a camera to the scene
        //This camera is super fast... you have been warned
        GameObject* camObj = new GameObject(this);
        renderer->camera = new Camera(0.1, 500.0, 30.0, 1.6);
        camObj->getTransform()->setLocalPosition(Vector3(5, .25, 0));
        camObj->setCamera(renderer->camera);
        camObj->getTransform()->setParent(root);
        camObj->addComponent(new KeyboardController());
        camObj->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 100, Math::PI / 2, 0)));

        //Texture* houseTex = new Texture("Resources/house_texture_v2.png", true, true);
        //renderer->loadTexture(houseTex);
        //Material* houseMat = renderer->createMaterial(Renderer::PR_OPAQUE);
        //houseMat->setTexture(houseTex);

        //GameObject* house = new GameObject(this);
        //house->setMesh(new House(1));
        //house->setMaterial(green);
        //house->getTransform()->setLocalPosition(Vector3(-10, 0, 0));
        //house->getTransform()->setParent(root);
        //house->getTransform()->name = "House";

        GameObject* plate = new GameObject(this);
        plate->setMesh(new Plate(1, .05, 24));
        plate->setMaterial(green);
        plate->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        plate->getTransform()->setParent(root);
        plate->getTransform()->name = "plate";




        return true;
    }


}