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


using namespace T3D;
namespace T3D
{
    bool AnimationTutorial::init() {
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
        Lamp* lamp = new Lamp(this);
        lamp->setMaterial(grey);
        lamp->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        lamp->getTransform()->setParent(root);

        lamp->base->setMaterial(grey);
        lamp->arm1->setMaterial(grey);
        lamp->arm2->setMaterial(grey);

        lamp->baseJoint->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 10, Math::PI / 4, 0)));
        lamp->elbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 4, 0, 0)));

        lamp->lampShade->setMaterial(grey);
        lamp->shadeJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 4, 0, 0)));

        GameObject* directionObject = new GameObject(this);
        directionObject->getTransform()->setLocalPosition(Vector3(5, 0, -5));
        LookAtBehaviour* lampDirectionBehaviour = new LookAtBehaviour(directionObject->getTransform());
        lamp->addComponent(lampDirectionBehaviour);
        //cube->addComponent(new LookAtBehaviour(sphere->getTransform()));
        
        //LampBehaviour* lampBehaviour = new LampBehaviour();
        //lampBehaviour->lampTransform = lamp->getTransform();
        //lamp->addComponent(lampBehaviour);

        //AnimationTest* animTask = new AnimationTest(this);
        //animTask->lampTransform = lamp->getTransform();
        //addTask(animTask);

        Animation* anim = new Animation(10.0);
        lamp->addComponent(anim);
        anim->addKey("ElbowJoint", 0, Quaternion(Vector3(0, 0, 0)), Vector3(0, 0.2, 0));
        anim->addKey("ElbowJoint", 5.0, Quaternion(Vector3(-Math::HALF_PI, 0, 0)), Vector3(0, 0.2, 0));
        anim->addKey("ElbowJoint", 7.0, Quaternion(Vector3(Math::HALF_PI, 0, 0)), Vector3(0, 0.2, 0));
        anim->addKey("ElbowJoint", 10.0, Quaternion(Vector3(0, 0, 0)), Vector3(0, 0.2, 0));
        anim->addKey("ShadeJoint", 0, Quaternion(Vector3(0, 0, 0)), Vector3(0, 0.2, 0));
        anim->addKey("ShadeJoint", 5.0, Quaternion(Vector3(0, 0, -Math::HALF_PI)), Vector3(0, 0.2, 0));
        anim->addKey("ShadeJoint", 7.0, Quaternion(Vector3(0, 0, Math::HALF_PI)), Vector3(0, 0.2, 0));
        anim->addKey("ShadeJoint", 10.0, Quaternion(Vector3(0, 0, 0)), Vector3(0, 0.2, 0));
        //anim->loop(true);
        anim->play();

        return true;
    }

}