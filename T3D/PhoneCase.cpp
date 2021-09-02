#include "PhoneCase.h"

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
	PhoneCase::PhoneCase(T3DApplication* app) :GameObject(app) {
		{
			//std::vector<Vector3> phoneCaseProfile;
			//phoneCaseProfile.push_back(Vector3(-0.2f, -0.1f, 0.0f));
			//phoneCaseProfile.push_back(Vector3(0.07f, -0.1f, 0.0f));
			//phoneCaseProfile.push_back(Vector3(0.07f, -0.11f, 0.0f));
			//phoneCaseProfile.push_back(Vector3(0.08f, -0.11f, 0.0f));
			//phoneCaseProfile.push_back(Vector3(0.08f, -0.1f, 0.0f));
			//phoneCaseProfile.push_back(Vector3(0.2f, -0.1f, 0.0f));
			//phoneCaseProfile.push_back(Vector3(0.2f, 0.1f, 0.0f));
			//phoneCaseProfile.push_back(Vector3(-0.2f, 0.1f, 0.0f));

			//arm 1
			std::vector<Vector3> armProfile;
			armProfile.push_back(Vector3(0.0f, -0.12f, 0.0f));
			armProfile.push_back(Vector3(0.014f, -0.114f, 0.0f));
			armProfile.push_back(Vector3(0.02f, -0.1f, 0.0f));
			armProfile.push_back(Vector3(0.02f, 0.1f, 0.0f));
			armProfile.push_back(Vector3(0.014f, 0.114f, 0.0f));
			armProfile.push_back(Vector3(0.0f, 0.12f, 0.0f));
			armProfile.push_back(Vector3(-0.014f, 0.114f, 0.0f));
			armProfile.push_back(Vector3(-0.02f, 0.1f, 0.0f));
			armProfile.push_back(Vector3(-0.02f, -0.1f, 0.0f));
			armProfile.push_back(Vector3(-0.014f, -0.114f, 0.0f));

			//create the first transform
			t.setLocalPosition(Vector3(0, 0, 0));
			t.setLocalRotation(Quaternion(Vector3(0, Math::PI / 2, 0)));
			t.setLocalScale(Vector3(0.01, 0.01, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
			armsp.addTransform(t);
			armsp.addTransform(t);
			//Adjust the scale for the next path instance
			t.setLocalScale(Vector3(0.9, 1, 1.0));
			armsp.addTransform(t);
			armsp.addTransform(t);

			//Adjust the position and scale for the next path instance
			t.setLocalPosition(Vector3(-0.0075, 0, 0));
			t.setLocalScale(Vector3(1, 1, 1.0));
			armsp.addTransform(t);
			//armsp.addTransform(t);

			//Adjust the position for the next path instance
			t.setLocalPosition(Vector3(0.0075, 0, 0));
			t.setLocalScale(Vector3(1, 1, 1.0));
			armsp.addTransform(t);
			//armsp.addTransform(t);

			//Adjust the position for the next path instance
			t.setLocalPosition(Vector3(0.1, 0, 0));
			t.setLocalScale(Vector3(0.9, 0, 1.0));
			armsp.addTransform(t);
			armsp.addTransform(t);

			//Adjust the scale for the final 'cap'
			//t.setLocalScale(Vector3(0.01, 0.01, 1.0));
			//armsp.addTransform(t);
			//armsp.addTransform(t);

			arm1 = new GameObject(app);
			arm1->setMesh(new Sweep(armProfile, armsp, false));
			arm1->getTransform()->setLocalPosition(Vector3(0, 0, 0)); // not correctly positioned yet
			//arm1->getTransform()->setLocalPosition(Vector3(0, 0.1, 0)); 
			arm1->getTransform()->setParent(getTransform()); // not correct attachment yet
			arm1->getTransform()->name = "Arm1";
		}
	}

}