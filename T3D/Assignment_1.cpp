#include "LampTutorial.h"
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
#include "PhoneCase.h"
#include "WineGlass.h"
#include "Assignment_1.h"


using namespace T3D;
namespace T3D
{
    bool Assignment_1::init() {
        WinGLApplication::init();
        //light to the scene
        GameObject* lightObj = new GameObject(this);
        Light* light = new Light(Light::Type::DIRECTIONAL);
        light->setAmbient(1, 1, 1);
        light->setDiffuse(1, 1, 1);
        light->setSpecular(1, 1, 1);
        lightObj->setLight(light);
        lightObj->getTransform()->
            setLocalRotation(Vector3(-45 * Math::DEG2RAD, 70 * Math::DEG2RAD, 0));
        lightObj->getTransform()->setParent(root);
        //camera
        //add a camera to the scene
        //This camera is super fast... you have been warned
        GameObject* camObj = new GameObject(this);
        renderer->camera = new Camera(0.1, 500.0, 45.0, 1.6);
        camObj->getTransform()->setLocalPosition(Vector3(0, 0.5, 3));
        camObj->setCamera(renderer->camera);
        camObj->getTransform()->setParent(root);
        camObj->addComponent(new KeyboardController());
        //material
        Material* green =
            renderer->createMaterial(Renderer::PR_OPAQUE);
        green->setDiffuse(0, 1, 0, 1);


        Material* grey = renderer->createMaterial(Renderer::PR_OPAQUE);
        grey->setDiffuse(0.8, 0.8, 0.9, 1);

       
        //PhoneCase* phoneCase = new PhoneCase(this);
        //phoneCase->setMaterial(grey);
        //phoneCase->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        //phoneCase->getTransform()->setParent(root);
        //phoneCase->arm1->setMaterial(grey);
        //phoneCase->phoneCase->setMaterial(grey);

        WineGlass* wineGlass = new WineGlass(this);
        wineGlass->setMaterial(grey);
        wineGlass->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        wineGlass->getTransform()->setParent(root);
        wineGlass->wineGlass->setMaterial(grey);

        return true;
    }

}