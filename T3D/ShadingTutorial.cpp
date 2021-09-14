#include "ShadingTutorial.h"
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
#include "GLShader.h"

using namespace T3D;
namespace T3D
{
	bool ShadingTutorial::init() {
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
        camObj->getTransform()->setLocalPosition(Vector3(0, 0, 20));
        camObj->getTransform()->setLocalRotation(Vector3(0, 0, 0));
        camObj->setCamera(renderer->camera);
        camObj->getTransform()->setParent(root);
        camObj->addComponent(new KeyboardController());



        Material* fixedGreen = renderer->createMaterial(Renderer::PR_OPAQUE);
        fixedGreen->setDiffuse(0.0, 0.6, 0, 1);
        fixedGreen->setShininess(20);
        Material* gouraudGreen = renderer->createMaterial(Renderer::PR_OPAQUE);
        gouraudGreen->setDiffuse(0.0, 0.6, 0, 1);
        gouraudGreen->setShininess(20);
        Material* phongGreen = renderer->createMaterial(Renderer::PR_OPAQUE);
        phongGreen->setDiffuse(0.0, 0.6, 0, 1);
        phongGreen->setShininess(20);

        GLShader* gouraudShader = new GLShader("Resources/vspecular.shader", "Resources/frag.shader");
        gouraudShader->compileShader();
        gouraudGreen->setShader(gouraudShader);

        GLShader* phongShader = new GLShader("Resources/phongVert.shader", "Resources/phongFrag.shader");
        phongShader->compileShader();
        phongGreen->setShader(phongShader);

        GameObject* sphere1 = new GameObject(this);
        sphere1->setMesh(new Sphere(1, 32));
        sphere1->setMaterial(fixedGreen);
        sphere1->getTransform()->setLocalPosition(Vector3(-3, 0, 0));
        sphere1->getTransform()->setParent(root);

        GameObject* sphere2 = new GameObject(this);
        sphere2->setMesh(new Sphere(1, 32));
        sphere2->setMaterial(gouraudGreen);
        sphere2->getTransform()->setLocalPosition(Vector3(0, 0, 0));
        sphere2->getTransform()->setParent(root);

        GameObject* sphere3 = new GameObject(this);
        sphere3->setMesh(new Sphere(1, 32));
        sphere3->setMaterial(phongGreen);
        sphere3->getTransform()->setLocalPosition(Vector3(3, 0, 0));
        sphere3->getTransform()->setParent(root);

		return true;
	}
}