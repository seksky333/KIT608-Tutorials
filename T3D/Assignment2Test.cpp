#include "Assignment2Test.h"
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
#include "RobotHand.h"


using namespace T3D;
namespace T3D
{
    const float legJPosX = 0.0;
    const float legJPosY = -0.1425;
    const float legJPosZ = 0.10;

    bool Assignment2Test::init() {
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
        //Lamp* lamp = new Lamp(this);
        //lamp->setMaterial(grey);
        //lamp->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        //lamp->getTransform()->setParent(root);
        //lamp->base->setMaterial(grey);
        //lamp->arm1->setMaterial(grey);
        //lamp->arm2->setMaterial(grey);
        //lamp->baseJoint->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 10, Math::PI / 4, 0)));
        //lamp->elbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 4, 0, 0)));
        //lamp->lampShade->setMaterial(grey);
        //lamp->shadeJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 4, 0, 0)));

        //GameObject* directionObject = new GameObject(this);
        //directionObject->getTransform()->setLocalPosition(Vector3(5, 0, -5));
        //LookAtBehaviour* lampDirectionBehaviour = new LookAtBehaviour(directionObject->getTransform());
        //lamp->addComponent(lampDirectionBehaviour);

        //LampBehaviour* lampBehaviour = new LampBehaviour();
        //lampBehaviour->lampTransform = lamp->getTransform();
        //lamp->addComponent(lampBehaviour);


        //AnimationTest* animTask = new AnimationTest(this);
        //animTask->lampTransform = lamp->getTransform();
        //addTask(animTask);




        Robot* robot = new Robot(this);
        robot->setMaterial(green);
        robot->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        robot->getTransform()->setParent(root);
        robot->body->setMaterial(green);
        robot->head->setMaterial(grey);
        robot->leftEye->setMaterial(grey);
        robot->leftShoulder->setMaterial(grey);
        robot->leftArm->setMaterial(green);
        robot->leftHand->setMaterial(grey);
        robot->leftLeg->setMaterial(green);
        robot->leftFoot->setMaterial(grey);
        robot->rightEye->setMaterial(grey);
        robot->rightShoulder->setMaterial(grey);
        robot->rightArm->setMaterial(green);
        robot->rightHand->setMaterial(grey);
        robot->rightLeg->setMaterial(green);
        robot->rightFoot->setMaterial(grey);

        GameObject* directionObject = new GameObject(this);
        directionObject->getTransform()->setLocalPosition(Vector3(5, 0, 0));
        LookAtBehaviour* directionBehaviour = new LookAtBehaviour(directionObject->getTransform());
        robot->addComponent(directionBehaviour);

        AnimationTest* animTask = new AnimationTest(this);
        animTask->lampTransform = robot->getTransform();
        addTask(animTask);

        //robot->leftShoulder->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::PI / 4)));
        robot->leftHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI, Math::PI / 2, 0)));
        robot->rightHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI, Math::PI / 2, 0)));
        //robot->headJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, -Math::PI / 4, 0)));
        //robot->leftArmJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, 0, Math::PI / 4)));
        //robot->headJoint->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::PI / 4, 0)));

         Animation* anim = new Animation(10.0);
         robot->addComponent(anim);
        anim->addKey("HeadJoint", 0, Quaternion(Vector3(0, 0, 0)), Vector3(0, 0.0, 0));
        anim->addKey("HeadJoint", 5.0, Quaternion(Vector3(0, -Math::HALF_PI, 0)), Vector3(0, 0.0, 0));
        anim->addKey("HeadJoint", 7.0, Quaternion(Vector3(0, Math::HALF_PI, 0)), Vector3(0, 0.0, 0));
        anim->addKey("HeadJoint", 10.0, Quaternion(Vector3(0, 0, 0)), Vector3(0, 0.0, 0));


        
        //anim->addKey("LeftLegJoint", 0, Quaternion(Vector3(legJPosX, legJPosY, legJPosZ)), Vector3(legJPosX -Math::HALF_PI, legJPosY, legJPosZ));
        //anim->addKey("LeftLegJoint", 5.0, Quaternion(Vector3(legJPosX, legJPosY, legJPosZ)), Vector3(legJPosX + Math::HALF_PI, legJPosY, legJPosZ));
        //anim->addKey("LeftLegJoint", 7.0, Quaternion(Vector3(0, 0, 0)), Vector3(0, 0, -Math::HALF_PI));
        //anim->addKey("LeftLegJoint", 10.0, Quaternion(Vector3(0, 0, 0)), Vector3(0, 0, Math::HALF_PI));

        anim->addKey("RightLegJoint", 0, Quaternion(Vector3(legJPosX, legJPosY, -legJPosZ)), Vector3(legJPosX, legJPosY, -legJPosZ));
        addRunningAnime("RightLegJoint", 1, 9, anim);
        anim->addKey("RightLegJoint", 10.0, Quaternion(Vector3(legJPosX, legJPosY, -legJPosZ)), Vector3(legJPosX, legJPosY, -legJPosZ));

        anim->addKey("LeftLegJoint", 0, Quaternion(Vector3(legJPosX, legJPosY, legJPosZ)), Vector3(legJPosX, legJPosY, legJPosZ));
        addRunningAnime("LeftLegJoint", 1, 9, anim);
        anim->addKey("LeftLegJoint", 10.0, Quaternion(Vector3(legJPosX, legJPosY, legJPosZ)), Vector3(legJPosX, legJPosY, legJPosZ));
        anim->loop(true);
        anim->play();
        return true;
    }

    void Assignment2Test::addRunningAnime(std::string element, int startFramePos, int endFramePos, Animation* anim) {
        float framePos = 0.0;
        for (int i = 1; i < 9; i++) {
            framePos = i;
            //if leftLeg
            if (element == "LeftLegJoint") {
                if (i % 2 == 0) {
                    anim->addKey(element, framePos, Quaternion(Vector3(legJPosX, legJPosY, legJPosZ - Math::HALF_PI / 2)), Vector3(legJPosX, legJPosY, legJPosZ));
                }else {
                    anim->addKey(element, framePos, Quaternion(Vector3(legJPosX, legJPosY, Math::HALF_PI / 2)), Vector3(legJPosX, legJPosY, legJPosZ));
                }
            }
            //if righttLeg
            else {
                if (i % 2 == 0) {
                    anim->addKey(element, framePos, Quaternion(Vector3(legJPosX, legJPosY, Math::HALF_PI / 2)), Vector3(legJPosX, legJPosY, -legJPosZ));
                }else {
                    anim->addKey(element, framePos, Quaternion(Vector3(legJPosX, legJPosY, -legJPosZ - Math::HALF_PI / 2)), Vector3(legJPosX, legJPosY, -legJPosZ));
                }
            }

        }
    }

}