#include "Task1and5.h"
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

    bool Task1and5::init() {
        WinGLApplication::init();

        //Create a skybox and add some fog
        renderer->loadSkybox("Resources/dsb");
        renderer->setFog(0.007f, 0.8f, 0.8f, 0.8f, 1.0f);
        renderer->toggleFog();

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

        //Create a material with a procedurally generated texture
        Texture* proctex = new Texture(512, 512);
        proctex->createFractal(Colour(255, 255, 255, 255), Colour(255, 255, 255, 255), 25.0f, false);
        renderer->loadTexture(proctex, true);
        Material* procmat = renderer->createMaterial(Renderer::PR_TERRAIN);
        procmat->setTexture(proctex, 50);
        procmat->setSpecular(0, 0, 0, 0);

        //Add some terrain
        GameObject* terrain = new GameObject(this);
        Terrain* terrainComponent = new Terrain();
        terrain->addComponent(terrainComponent);
        terrainComponent->createTerrain("Resources/yosemite_hm.bmp", 500, 15);
        //terrainComponent->createFractalTerrain(256,500,15,2.0); // procedurally generate terrain
        terrain->setMaterial(procmat);
        terrain->getTransform()->setLocalPosition(Vector3(0, -6, 0));
        terrain->getTransform()->setParent(root);
        terrain->getTransform()->name = "Terrain";

        //material
        Material* green =
            renderer->createMaterial(Renderer::PR_OPAQUE);
        green->setDiffuse(0, 1, 0, 1);

        Material* grey = renderer->createMaterial(Renderer::PR_OPAQUE);
        grey->setDiffuse(0.8, 0.8, 0.9, 1);

        Material* blue = renderer->createMaterial(Renderer::PR_OPAQUE);
        blue->setDiffuse(0, 0, 1, 1);

        Robot* robot1 = new Robot(this);
        robot1->setMaterial(green);
        robot1->getTransform()->setLocalPosition(Vector3(0, 0, 1));
        robot1->getTransform()->setParent(root);
        robot1->body->setMaterial(green);
        robot1->head->setMaterial(grey);
        robot1->leftEye->setMaterial(grey);
        robot1->leftShoulder->setMaterial(grey);
        robot1->leftArm->setMaterial(green);
        robot1->leftHand->setMaterial(grey);
        robot1->leftLeg->setMaterial(green);
        robot1->leftFoot->setMaterial(grey);
        robot1->rightEye->setMaterial(grey);
        robot1->rightShoulder->setMaterial(grey);
        robot1->rightArm->setMaterial(green);
        robot1->rightHand->setMaterial(grey);
        robot1->rightLeg->setMaterial(green);
        robot1->rightFoot->setMaterial(grey);

        Robot* robot2 = new Robot(this);
        robot2->setMaterial(blue);
        robot2->getTransform()->setLocalPosition(Vector3(0, 0, -1));
        robot2->getTransform()->setParent(root);
        robot2->body->setMaterial(blue);
        robot2->head->setMaterial(grey);
        robot2->leftEye->setMaterial(grey);
        robot2->leftShoulder->setMaterial(grey);
        robot2->leftArm->setMaterial(blue);
        robot2->leftHand->setMaterial(grey);
        robot2->leftLeg->setMaterial(blue);
        robot2->leftFoot->setMaterial(grey);
        robot2->rightEye->setMaterial(grey);
        robot2->rightShoulder->setMaterial(grey);
        robot2->rightArm->setMaterial(blue);
        robot2->rightHand->setMaterial(grey);
        robot2->rightLeg->setMaterial(blue);
        robot2->rightFoot->setMaterial(grey);

        //camera
        //add a camera to the scene
        //This camera is super fast... you have been warned
        GameObject* camObj = new GameObject(this);
        renderer->camera = new Camera(0.1, 500.0, 30.0, 1.6);
        camObj->getTransform()->setLocalPosition(Vector3(5, .25, 0));
        camObj->setCamera(renderer->camera);
        camObj->getTransform()->setParent(root);
        camObj->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 100, Math::PI / 2, 0)));

        Texture* houseTex = new Texture("Resources/house_texture_v2.png", true, true);
        renderer->loadTexture(houseTex);
        Material* houseMat = renderer->createMaterial(Renderer::PR_OPAQUE);
        houseMat->setTexture(houseTex);

        GameObject* house = new GameObject(this);
        house->setMesh(new House(1));
        house->setMaterial(houseMat);
        house->getTransform()->setLocalPosition(Vector3(-10, 0, 0));
        house->getTransform()->setParent(root);
        house->getTransform()->name = "House";


        GameObject* directionObject = new GameObject(this);
        directionObject->getTransform()->setLocalPosition(Vector3(5, 0, 0));
        LookAtBehaviour* lookAtRobot1 = new LookAtBehaviour(directionObject->getTransform());
        LookAtBehaviour* lookAtRobot2 = new LookAtBehaviour(directionObject->getTransform());
        robot1->addComponent(lookAtRobot1);
        robot2->addComponent(lookAtRobot2);

        //Anime tasks
        CameraTask* cameraTask = new CameraTask(this);
        cameraTask->camObj = camObj;
        addTask(cameraTask);

        Robot1Task* robot1AnimeTask = new Robot1Task(this);
        robot1AnimeTask->robot= robot1;
        addTask(robot1AnimeTask);

        Robot2Task* robot2AnimeTask = new Robot2Task(this);
        robot2AnimeTask->robot = robot2;
        addTask(robot2AnimeTask);

        robot1->body->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::PI - (Math::PI/4), 0)));
        robot1->leftHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI, Math::PI / 2, 0)));
        robot1->rightHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI, Math::PI / 2, 0)));

        robot2->body->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::PI/4, 0)));
        robot2->leftHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI, Math::PI / 2, 0)));
        robot2->rightHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI, Math::PI / 2, 0)));


        TableWithGlass* tableWithGlass = new TableWithGlass(this, .5, .6, .2, 2);
        tableWithGlass->setMaterial(green);
        tableWithGlass->getTransform()->setLocalPosition(Vector3(0.5, -.2, 0));
        tableWithGlass->getTransform()->setParent(root);
        tableWithGlass->base->setMaterial(blue);
        tableWithGlass->leg1->setMaterial(grey);
        tableWithGlass->leg2->setMaterial(grey);
        tableWithGlass->leg3->setMaterial(grey);
        tableWithGlass->leg4->setMaterial(grey);
        tableWithGlass->wineGlass->setMaterial(blue);


        WineGlassTask* wineGlassTask = new WineGlassTask(this);
        wineGlassTask->gameObj = tableWithGlass->wineGlass;
        wineGlassTask->base = tableWithGlass->base;
        wineGlassTask->leg1 = tableWithGlass->leg1;
        wineGlassTask->leg2 = tableWithGlass->leg2;
        wineGlassTask->leg3 = tableWithGlass->leg3;
        wineGlassTask->leg4 = tableWithGlass->leg4;
        addTask(wineGlassTask);


        //Create a textured material by adding text
        Texture* texttex = new Texture(128, 32);
        /*texttex->clear(Colour(48, 48, 48, 255));*/
        texttex->clear(Colour(255, 255, 255, 255));
        font* f = getFont("resources/FreeSans.ttf", 16);
        if (f != NULL) {
            texttex->writeText(2, 0, "This", Colour(0, 255, 0, 255), f->getFont());
            texttex->writeText(42, 0, "is", Colour(0, 255, 0, 255), f->getFont());
            texttex->writeText(64, 0, "boring!", Colour(255, 0, 0, 0), f->getFont());
        }
        renderer->loadTexture(texttex, true);
        Material* textmat = renderer->createMaterial(Renderer::PR_OPAQUE);
        textmat->setTexture(texttex, 1);
        textmat->setEmissive(1, 1, 1, 1);

        //Create a textured material by adding text
        Texture* texttex1 = new Texture(128, 32);
        /*texttex->clear(Colour(48, 48, 48, 255));*/
        texttex1->clear(Colour(255, 255, 255, 255));
        if (f != NULL) {
            texttex1->writeText(12, 0, "What", Colour(255, 0, 0, 255), f->getFont());
            texttex1->writeText(60, 0, "the", Colour(255, 0, 0, 255), f->getFont());
            texttex1->writeText(96, 0, "...", Colour(255, 0, 0, 0), f->getFont());
        }
        renderer->loadTexture(texttex1, true);
        Material* textmat1 = renderer->createMaterial(Renderer::PR_OPAQUE);
        textmat1->setTexture(texttex1, 1);
        textmat1->setEmissive(1, 1, 1, 1);

        //Create a textured material by adding text
        Texture* texttex2 = new Texture(128, 32);
        font* f2 = getFont("resources/FreeSans.ttf", 14);
        /*texttex->clear(Colour(48, 48, 48, 255));*/
        texttex2->clear(Colour(255, 255, 255, 255));
        if (f != NULL) {
            texttex2->writeText(2, 0, "Now's", Colour(255, 0, 0, 0), f2->getFont());
            texttex2->writeText(44, 0, "super", Colour(255, 0, 0, 0), f2->getFont());
            texttex2->writeText(84, 0, "boring", Colour(255, 0, 0, 0), f2->getFont());
        }
        renderer->loadTexture(texttex2, true);
        Material* textmat2 = renderer->createMaterial(Renderer::PR_OPAQUE);
        textmat2->setTexture(texttex2, 1);
        textmat2->setEmissive(1, 1, 1, 1);

        //Create a textured material by adding text
        Texture* texttex3 = new Texture(128, 32);
        texttex3->clear(Colour(48, 48, 48, 255));
        if (f != NULL) {
            texttex3->writeText(24, 0, "THE", Colour(255, 255, 255, 0), f->getFont());
            texttex3->writeText(72, 0, "END", Colour(255, 255, 255, 0), f->getFont());
        }
        renderer->loadTexture(texttex3, true);
        Material* textmat3 = renderer->createMaterial(Renderer::PR_OPAQUE);
        textmat3->setTexture(texttex3, 1);
        textmat3->setEmissive(1, 1, 1, 1);

        //Add a This is boring message
        GameObject* billboard = new GameObject(this);
        Billboard* billboardComponent = new Billboard(renderer->camera->gameObject->getTransform(), true);
        billboard->addComponent(billboardComponent);
        billboard->setMaterial(textmat);			
        billboard->getTransform()->setLocalPosition(Vector3(-1, 1., 0));
        billboard->getTransform()->setLocalScale(Vector3(2, 2, 1));
        billboard->getTransform()->setParent(root);
        billboard->getTransform()->name = "Billboard";

        GameObject* billboard1 = new GameObject(this);
        Billboard* billboardComponent1 = new Billboard(renderer->camera->gameObject->getTransform(), true);
        billboard1->addComponent(billboardComponent1);
        billboard1->setMaterial(textmat1);
        billboard1->getTransform()->setLocalPosition(Vector3(-1, 1., 0));
        billboard1->getTransform()->setLocalScale(Vector3(2, 2, 1));
        billboard1->getTransform()->setParent(root);
        billboard1->getTransform()->name = "Billboard1";
        billboard1->setVisible(false);

        GameObject* billboard2 = new GameObject(this);
        Billboard* billboardComponent2 = new Billboard(renderer->camera->gameObject->getTransform(), true);
        billboard2->addComponent(billboardComponent2);
        billboard2->setMaterial(textmat2);
        billboard2->getTransform()->setLocalPosition(Vector3(-1, 1., 0));
        billboard2->getTransform()->setLocalScale(Vector3(2, 2, 1));
        billboard2->getTransform()->setParent(root);
        billboard2->getTransform()->name = "Billboard2";
        billboard2->setVisible(false);

        GameObject* billboard3 = new GameObject(this);
        Billboard* billboardComponent3 = new Billboard(renderer->camera->gameObject->getTransform(), true);
        billboard3->addComponent(billboardComponent3);
        billboard3->setMaterial(textmat3);
        billboard3->getTransform()->setLocalPosition(Vector3(-1, 1., 0));
        billboard3->getTransform()->setLocalScale(Vector3(2, 2, 1));
        billboard3->getTransform()->setParent(root);
        billboard3->getTransform()->name = "Billboard3";
        billboard3->setVisible(false);

        BillboardTask* billTask = new BillboardTask(this);
        billTask->gameObj = billboard;
        billTask->gameObj1 = billboard1;
        billTask->gameObj2 = billboard2;
        billTask->gameObj3 = billboard3;
        addTask(billTask);

        //sound effect
        addTask(new SoundTestTask(this));

        return true;
    }


    void Task1and5::addRobotWalking(std::string element, int startFramePos, int endFramePos, Animation* anim) {
        float framePos = 0.0;
        for (int i = 1; i < 9; i++) {
            framePos = i;
            //if leftLeg
            if (element == "LeftLegJoint") {
                if (i % 2 == 0) {
                    anim->addKey(element, framePos, Quaternion(Vector3(legJPosX, legJPosY, legJPosZ - Math::HALF_PI / 3.5)), Vector3(legJPosX, legJPosY, legJPosZ));
                }else {
                    anim->addKey(element, framePos, Quaternion(Vector3(legJPosX, legJPosY, Math::HALF_PI / 3.5)), Vector3(legJPosX, legJPosY, legJPosZ));
                }
            }
            //if righttLeg
            else {
                if (i % 2 == 0) {
                    anim->addKey(element, framePos, Quaternion(Vector3(legJPosX, legJPosY, Math::HALF_PI / 3.5)), Vector3(legJPosX, legJPosY, -legJPosZ));
                }else {
                    anim->addKey(element, framePos, Quaternion(Vector3(legJPosX, legJPosY, -legJPosZ - Math::HALF_PI / 3.5)), Vector3(legJPosX, legJPosY, -legJPosZ));
                }
            }

        }
    }

}