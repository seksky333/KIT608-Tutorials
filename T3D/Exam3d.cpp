#include "Exam3d.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include "Component.h"
#include "Transform.h"
#include "GLRenderer.h"
#include "LookAtBehaviour.h"
#include "KeyboardController.h"
#include "Input.h"
#include "Math.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Cylinder.h"
#include "Animation.h"
#include "Tablet.h"
#include "House.h"
#include "Terrain.h"
#include "SoundTestTask.h"
#include "Billboard.h"
#include "BillboardTask.h"
#include "CompositePlateTask.h"
#include "SpoonTask.h"
#include "GLShader.h"

using namespace T3D;
namespace T3D
{


    bool Exam3d::init() {
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



        //material
        Material* green =
            renderer->createMaterial(Renderer::PR_OPAQUE);
        green->setDiffuse(0, 1, 0, 1);

        Material* grey = renderer->createMaterial(Renderer::PR_OPAQUE);
        grey->setDiffuse(0.8, 0.8, 0.9, 1);

        Material* blue = renderer->createMaterial(Renderer::PR_OPAQUE);
        blue->setDiffuse(0, 0, 1, 1);



        Material* spoonGrey = renderer->createMaterial(Renderer::PR_OPAQUE);
       spoonGrey->setDiffuse(0.8, 0.8, 0.9, 1);
       spoonGrey->setShininess(20);

       GLShader* gouraudShader = new GLShader("Resources/vspecular.shader", "Resources/frag.shader");
       gouraudShader->compileShader();
       spoonGrey->setShader(gouraudShader);

        //camera
        //add a camera to the scene
        //This camera is super fast... you have been warned
        GameObject* camObj = new GameObject(this);
        renderer->camera = new Camera(0.1, 500.0, 30.0, 1.6);
        camObj->getTransform()->setLocalPosition(Vector3(5, .25, 0));
        camObj->setCamera(renderer->camera);
        camObj->getTransform()->setParent(root);
        camObj->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 100, Math::PI / 2, 0)));

        GameObject* directionObject = new GameObject(this);
        directionObject->getTransform()->setLocalPosition(Vector3(-20, 0, 0));
        LookAtBehaviour* lookAtCam= new LookAtBehaviour(directionObject->getTransform());
        camObj->addComponent(lookAtCam);

        Texture* houseTex = new Texture("Resources/house_texture_v2.png", true, true);
        renderer->loadTexture(houseTex);
        Material* houseMat = renderer->createMaterial(Renderer::PR_OPAQUE);
        houseMat->setTexture(houseTex);

        Texture* plateTex = new Texture("Resources/plate_texture.png", true, true);
        renderer->loadTexture(plateTex);
        Material* plateMat = renderer->createMaterial(Renderer::PR_OPAQUE);
        plateMat->setTexture(plateTex);

        GameObject* house = new GameObject(this);
        house->setMesh(new House(1));
        house->setMaterial(houseMat);
        house->getTransform()->setLocalPosition(Vector3(-20, 0, 0));
        house->getTransform()->setParent(root);
        house->getTransform()->name = "House";

        CompositePlate* compositePlate = new CompositePlate(this);
        compositePlate->setMaterial(grey);
        compositePlate->getTransform()->setLocalPosition(Vector3(0, 0, 1));
        compositePlate->getTransform()->setParent(root);
        compositePlate->getTransform()->name = "CompositePlate";
        compositePlate->plate->setMaterial(plateMat);
        compositePlate->leftEye->setMaterial(blue);
        compositePlate->rightEye->setMaterial(blue);
        compositePlate->rightShoulder->setMaterial(grey);
        compositePlate->rightArm->setMaterial(blue);
        compositePlate->rightHand->setMaterial(grey);
        compositePlate->leftShoulder->setMaterial(grey);
        compositePlate->leftArm->setMaterial(blue);
        compositePlate->leftHand->setMaterial(grey);
        compositePlate->rightLeg->setMaterial(blue);
        compositePlate->rightFoot->setMaterial(grey);
        compositePlate->leftLeg->setMaterial(blue);
        compositePlate->leftFoot->setMaterial(grey);

        Spoon* spoon = new Spoon(this);
        spoon->setMaterial(spoonGrey);
        spoon->getTransform()->setLocalPosition(Vector3(0, 0, -1));
        spoon->getTransform()->setParent(root);
        spoon->spoonBody->setMaterial(spoonGrey);
        spoon->spoonHead->setMaterial(spoonGrey);
        spoon->rightLeg->setMaterial(green);
        spoon->leftLeg->setMaterial(green);


        //Create a textured material by adding text
        Texture* texttex3 = new Texture(128, 32);
        texttex3->clear(Colour(48, 48, 48, 255));
        font* f = getFont("resources/FreeSans.ttf", 16);
        if (f != NULL) {
            texttex3->writeText(24, 0, "THE", Colour(255, 255, 255, 0), f->getFont());
            texttex3->writeText(72, 0, "END", Colour(255, 255, 255, 0), f->getFont());
        }
        renderer->loadTexture(texttex3, true);
        Material* textmat3 = renderer->createMaterial(Renderer::PR_OPAQUE);
        textmat3->setTexture(texttex3, 1);
        textmat3->setEmissive(1, 1, 1, 1);

        GameObject* billboard3 = new GameObject(this);
        Billboard* billboardComponent3 = new Billboard(renderer->camera->gameObject->getTransform(), true);
        billboard3->addComponent(billboardComponent3);
        billboard3->setMaterial(textmat3);
        billboard3->getTransform()->setLocalPosition(Vector3(-1, 0., 0));
        billboard3->getTransform()->setLocalScale(Vector3(2, 2, 1));
        billboard3->getTransform()->setParent(root);
        billboard3->getTransform()->name = "Billboard3";
        billboard3->setVisible(false);

        BillboardTask* billTask = new BillboardTask(this);
        billTask->gameObj3 = billboard3;
        addTask(billTask);

        CompositePlateTask* plateAnimeTask = new CompositePlateTask(this);
        plateAnimeTask->compositePlate = compositePlate;
        addTask(plateAnimeTask);

        SpoonTask* spoonTask = new SpoonTask(this);
        spoonTask->spoon = spoon;
        addTask(spoonTask);


        //sound effect
        addTask(new SoundTestTask(this));

        return true;
    }


}