#include "SpoonBody.h"

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
#include "Sweep.h"
#include "SweepPath.h"


namespace T3D
{
	SpoonBody::SpoonBody(T3DApplication* app) :GameObject(app) {
		{
			//wineGlass
			std::vector<Vector3> spoonBodyProfile;
			spoonBodyProfile.push_back(Vector3(0.0f, -0.2f, 0.0f));
			spoonBodyProfile.push_back(Vector3(0.01f, -0.2f, 0.0f));
			spoonBodyProfile.push_back(Vector3(0.01f,  0.2f, 0.0f));


			spoonBodySP.makeCirclePath(0, 6 );

			//lampShade attaches to shadeJoint
			spoonBody = new GameObject(app);
			spoonBody->setMesh(new Sweep(spoonBodyProfile, spoonBodySP, true));
			spoonBody->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			spoonBody->getTransform()->setParent(getTransform());
			spoonBody->getTransform()->name = "Spoon Body";
			spoonBodySP.addTransform(t);
		}
	}


}