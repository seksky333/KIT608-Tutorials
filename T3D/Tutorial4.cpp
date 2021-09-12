#include "Tutorial4.h"
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
#include "Tablet.h"
#include "Lamp.h"
#include "Rectangle.h"
#include "TableWithGlass.h"

using namespace T3D;
namespace T3D
{
    bool Tutorial4::init() {
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
        GameObject* camObj = new GameObject(this);
        renderer->camera = new Camera(0.1, 500.0, 45.0, 1.6);
        camObj->getTransform()->setLocalPosition(Vector3(0, 0, 20));
        camObj->getTransform()->setLocalRotation(Vector3(0, 0, 0));
        camObj->setCamera(renderer->camera);
        camObj->getTransform()->setParent(root);
        camObj->addComponent(new KeyboardController());
        //material
        Material* green =
            renderer->createMaterial(Renderer::PR_OPAQUE);
        green->setDiffuse(0, 1, 0, 1);

        Material* grey = renderer->createMaterial(Renderer::PR_OPAQUE);
        grey->setDiffuse(0.8, 0.8, 0.9, 1);

        GameObject* shape = new GameObject(this);
        //shape->setMesh(new Pyramid(1));
        //shape->setMesh(new Cylinder(.1, .1, 16));
        //densitiy can only works for 6
        //shape->setMesh(new Tablet(Vector3(12,.5,6), .3, 1, .3, 6));
        //shape->setMesh(new Rectangle(Vector3(12,.5,6)));
        //shape->setMesh(new Cube(1));
        //shape->setMaterial(green);
        //shape->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        //shape->getTransform()->setParent(root);
        //shape->getTransform()->name = "Shape";
  
        //TableWithGlass* tableWithGlass = new TableWithGlass(this);
        //tableWithGlass->setMaterial(green);
        //tableWithGlass->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        //tableWithGlass->getTransform()->setParent(root);
        //
        //tableWithGlass->base->setMaterial(green);
        //tableWithGlass->leg1->setMaterial(grey);
        //tableWithGlass->leg2->setMaterial(grey);
        //tableWithGlass->leg3->setMaterial(grey);
        //tableWithGlass->leg4->setMaterial(grey);
        //tableWithGlass->wineGlass->setMaterial(grey);


        return true;
    }
}
