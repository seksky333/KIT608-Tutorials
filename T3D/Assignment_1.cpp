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
#include "Sphere.h"
#include "Lamp.h"
#include "Tablet.h"
#include "WineGlass.h"
#include "TableWithGlass.h"
#include "Robot.h"
#include "RobotHand.h"
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

        Material* red = renderer->createMaterial(Renderer::PR_OPAQUE);
        red->setDiffuse(1, 0, 0, 1);

        Material* blue = renderer->createMaterial(Renderer::PR_OPAQUE);
        blue->setDiffuse(0, 0, 1, 1);


       /*Part 1*/
        WineGlass* wineGlass = new WineGlass(this);
        wineGlass->setMaterial(grey);
        wineGlass->getTransform()->setLocalPosition(Vector3(0, 0, 3));
        wineGlass->getTransform()->setParent(root);
        wineGlass->wineGlass->setMaterial(grey);

        /*Part 2*/
        TableWithGlass* tableWithGlass = new TableWithGlass(this, 1.2, .6, .3, 3);
        tableWithGlass->setMaterial(green);
        tableWithGlass->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        tableWithGlass->getTransform()->setParent(root);
        tableWithGlass->base->setMaterial(blue);
        tableWithGlass->leg1->setMaterial(grey);
        tableWithGlass->leg2->setMaterial(grey);
        tableWithGlass->leg3->setMaterial(grey);
        tableWithGlass->leg4->setMaterial(grey);
        tableWithGlass->wineGlass->setMaterial(red);

        /*Part 3*/
        GameObject* tablet = new GameObject(this);
        tablet->setMaterial(grey);
        tablet->setMesh(new Tablet(Vector3(12, .5, 6), .3, 1, .3, 6));
        tablet->getTransform()->setLocalPosition(Vector3(0, -3, 0));
        tablet->getTransform()->setParent(root);

        /*Part 4*/
        Robot* robot = new Robot(this);
        robot->setMaterial(green);
        robot->getTransform()->setLocalPosition(Vector3(0, 0, -3));
        robot->getTransform()->setParent(root);
        robot->body->setMaterial(green);
        robot->head->setMaterial(grey);
        robot->leftShoulder->setMaterial(grey);
        robot->leftArm->setMaterial(green);
        robot->leftHand->setMaterial(grey);
        robot->leftLeg->setMaterial(green);
        robot->leftFoot->setMaterial(grey);
        robot->rightShoulder->setMaterial(grey);
        robot->rightArm->setMaterial(green);
        robot->rightHand->setMaterial(grey);
        robot->rightLeg->setMaterial(green);
        robot->rightFoot->setMaterial(grey);

        robot->leftShoulder->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::PI / 4)));
        robot->leftHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI, Math::PI / 2, 0)));

        robot->rightHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI, Math::PI / 2, 0)));

        //robot->leftArmJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::PI / 4)));
        //robot->headJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::PI / 4, 0)));
        
        return true;
    }

}