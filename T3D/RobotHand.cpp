#include "RobotHand.h"
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
	RobotHand::RobotHand(T3DApplication* app) :GameObject(app) {
		{
			
			std::vector<Vector3> robotHandProfile;
			//1
			robotHandProfile.push_back(Vector3(0.0f, -0.1f, 0.0f));
			robotHandProfile.push_back(Vector3(0.025f, -0.095f, 0.0f));
			//3
			robotHandProfile.push_back(Vector3(0.050f, -0.085f, 0.0f));
			robotHandProfile.push_back(Vector3(0.085f, -0.075f, 0.0f));
			//5
			robotHandProfile.push_back(Vector3(0.1f, -0.025f, 0.0f));
			robotHandProfile.push_back(Vector3(0.1f, 0.1f, 0.0f));
			//7
			robotHandProfile.push_back(Vector3(0.075f, 0.1f, 0.0f));
			robotHandProfile.push_back(Vector3(0.075f, 0.1f, 0.0f));
			//9
			robotHandProfile.push_back(Vector3(0.050f, -0.040f, 0.0f));
			robotHandProfile.push_back(Vector3(0.030f, -0.060f, 0.0f));
			//11
			robotHandProfile.push_back(Vector3(0.020f, -0.070f, 0.0f));
			robotHandProfile.push_back(Vector3(0.0f, -0.075f, 0.0f));
			//13
			robotHandProfile.push_back(Vector3(-0.020f, -0.070f, 0.0f));
			robotHandProfile.push_back(Vector3(-0.030f, -0.060f, 0.0f));
			//15
			robotHandProfile.push_back(Vector3(-0.050f, -0.040f, 0.0f));
			robotHandProfile.push_back(Vector3(-0.075f, 0.1f, 0.0f));
			//17
			robotHandProfile.push_back(Vector3(-0.075f, 0.1f, 0.0f));
			robotHandProfile.push_back(Vector3(-0.1f, 0.1f, 0.0f));
			//19
			robotHandProfile.push_back(Vector3(-0.1f, -0.025f, 0.0f));
			robotHandProfile.push_back(Vector3(-0.085f, -0.075f, 0.0f));
			//21
			robotHandProfile.push_back(Vector3(-0.050f, -0.085f, 0.0f));
			robotHandProfile.push_back(Vector3(-0.025f, -0.095f, 0.0f));

			//create the first transform
			t.setLocalPosition(Vector3(-0.01, 0, 0.0));
			t.setLocalRotation(Quaternion(Vector3(0, Math::PI / 2, 0)));
			t.setLocalScale(Vector3(0.01, 0.01, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
			robotHandSP.addTransform(t);
			robotHandSP.addTransform(t);
			//Adjust the scale for the next path instance
			t.setLocalScale(Vector3(0.9, 1, 1.0));
			robotHandSP.addTransform(t);
			robotHandSP.addTransform(t);
			//Adjust the position and scale for the next path instance
			t.setLocalPosition(Vector3(-0.0075, 0, 0));
			t.setLocalScale(Vector3(1, 1, 1.0));
			robotHandSP.addTransform(t);
			robotHandSP.addTransform(t);
			//Adjust the position for the next path instance
			t.setLocalPosition(Vector3(0.0075, 0, 0));
			robotHandSP.addTransform(t);
			robotHandSP.addTransform(t);
			//Adjust the position for the next path instance
			t.setLocalPosition(Vector3(0.01, 0, 0));
			t.setLocalScale(Vector3(0.9, 1, 1.0));
			robotHandSP.addTransform(t);
			robotHandSP.addTransform(t);

			//Adjust the scale for the final 'cap'
			t.setLocalScale(Vector3(0.01, 0.01, 1.0));
			robotHandSP.addTransform(t);
			robotHandSP.addTransform(t);

			robotHand = new GameObject(app);
			robotHand->setMesh(new Sweep(robotHandProfile, robotHandSP, false));
			robotHand->getTransform()->setLocalPosition(Vector3(0, 0, 0)); // not correctly positioned yet
			robotHand->getTransform()->setParent(getTransform()); // not correct attachment yet
			robotHand->getTransform()->name = "Robot Hand";
		}
	}
}
