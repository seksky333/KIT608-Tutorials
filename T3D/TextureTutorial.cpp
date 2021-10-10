#include "TextureTutorial.h"
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
#include "TCube.h"
#include "TCylinder.h"
#include "House.h"

using namespace T3D;
namespace T3D
{
    bool TextureTutorial::init() {
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
        camObj->getTransform()->setLocalPosition(Vector3(-1, 2, 5));
        camObj->setCamera(renderer->camera);
        camObj->getTransform()->setParent(root);
        camObj->addComponent(new KeyboardController());
        //material
        Material* green =
            renderer->createMaterial(Renderer::PR_OPAQUE);
        green->setDiffuse(0, 1, 0, 1);

        Material* grey = renderer->createMaterial(Renderer::PR_OPAQUE);
        grey->setDiffuse(0.8, 0.8, 0.9, 1);

        Texture* houseTex = new Texture("Resources/house_texture.png", true, true);
        renderer->loadTexture(houseTex);
        Material* houseMat = renderer->createMaterial(Renderer::PR_OPAQUE);
        houseMat->setTexture(houseTex);

        //Texture* cratetex = new Texture("Resources/crate013jc.jpg", true, true);
        //renderer->loadTexture(cratetex);
        //Material* cratemat = renderer->createMaterial(Renderer::PR_OPAQUE);
        //cratemat->setTexture(cratetex);

        //Texture* barreltex = new Texture("Resources/ExplosiveBarrel.jpg", true, true);
        //renderer->loadTexture(barreltex);
        //Material* barrelmat = renderer->createMaterial(Renderer::PR_OPAQUE);
        //barrelmat->setTexture(barreltex);

        //GameObject* cube = new GameObject(this);
        //cube->setMesh(new TCube(1));
        //cube->setMaterial(cratemat);
        //cube->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        //cube->getTransform()->setParent(root);
        //cube->getTransform()->name = "TCube";

        //GameObject* shape = new GameObject(this);
        //shape->setMesh(new TCylinder(.1, .1, 8));
        //shape->setMaterial(green);
        //shape->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        //shape->getTransform()->setParent(root);
        //shape->getTransform()->name = "Shape";

        GameObject* house = new GameObject(this);
        house->setMesh(new House(1));
        house->setMaterial(houseMat);
        house->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        house->getTransform()->setParent(root);
        house->getTransform()->name = "House";

        return true;
    }
}
