#include "Lamp.h"
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
#include "Rectangle.h"
#include "Sweep.h"
#include "SweepPath.h"
#include "Spoon.h"
#include "RobotHand.h"

namespace T3D
{
	Spoon::Spoon(T3DApplication* app) :GameObject(app) {
		{

			std::vector<Vector3> spoonBodyProfile;
			spoonBodyProfile.push_back(Vector3(0.0f, -0.4f, 0.0f));
			spoonBodyProfile.push_back(Vector3(0.01f, -0.4f, 0.0f));
			spoonBodyProfile.push_back(Vector3(0.01f, 0.4f, 0.0f));


			spoonBodySP.makeCirclePath(0, 6);

			//lampShade attaches to shadeJoint
			spoonBody = new GameObject(app);
			spoonBody->setMesh(new Sweep(spoonBodyProfile, spoonBodySP, true));
			spoonBody->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			spoonBody->getTransform()->setParent(getTransform());
			spoonBody->getTransform()->name = "Spoon Body";
			spoonBodySP.addTransform(t);


			////headJoint
			headJoint = new GameObject(app);
			headJoint->getTransform()->setParent(spoonBody->getTransform());
			headJoint->getTransform()->name = "HeadJoint";


			spoonHead = new GameObject(app);
			spoonHead->setMesh(new Cylinder(.1, .01, 48));
			spoonHead->getTransform()->setLocalPosition(Vector3(0, 0.4, 0));
			spoonHead->getTransform()->setParent(headJoint->getTransform());
			spoonHead->getTransform()->name = "Spoon Head";

			spoonHead->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 2, Math::PI / 2, 0)));

			//rightLegJoint
			rightLegJoint = new GameObject(app);
			rightLegJoint->getTransform()->setLocalPosition(Vector3(0.0, -.45, -.070));
			rightLegJoint->getTransform()->setParent(spoonBody->getTransform());
			rightLegJoint->getTransform()->name = "RightLegJoint";

			std::vector<Vector3> rightLegProfile;
			rightLegProfile = getLegProfile();
			rightLegSP.makeCirclePath(0, 6 * 20);

			rightLeg = new GameObject(app);
			rightLeg->setMesh(new Sweep(rightLegProfile, rightLegSP, true));
			rightLeg->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			rightLeg->getTransform()->setParent(rightLegJoint->getTransform());
			rightLeg->getTransform()->name = "RightLeg";
			rightLegSP.addTransform(t);

			rightLeg->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 4, 0, 0)));


			//leftLegJoint
			leftLegJoint = new GameObject(app);
			leftLegJoint->getTransform()->setLocalPosition(Vector3(0, -.45, 0.070));
			leftLegJoint->getTransform()->setParent(spoonBody->getTransform());
			leftLegJoint->getTransform()->name = "LeftLegJoint";

			std::vector<Vector3> leftLegProfile;
			leftLegProfile = getLegProfile();
			leftLegSP.makeCirclePath(0, 6 * 20);

			leftLeg = new GameObject(app);
			leftLeg->setMesh(new Sweep(leftLegProfile, leftLegSP, true));
			leftLeg->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			leftLeg->getTransform()->setParent(leftLegJoint->getTransform());
			leftLeg->getTransform()->name = "LeftLeg";
			leftLegSP.addTransform(t);

			leftLeg->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 4, 0, 0)));
		}

	}
		std::vector<Vector3> Spoon::getLegProfile() {
			std::vector<Vector3> legProfile;
			legProfile.push_back(Vector3(0.01f, -0.1f, 0.0f));
			legProfile.push_back(Vector3(0.01f, -0.1f, 0.0f));
			legProfile.push_back(Vector3(0.01f, -0.05f, 0.0f));
			legProfile.push_back(Vector3(0.01f, -0.0f, 0.0f));
			legProfile.push_back(Vector3(0.01f, 0.05f, 0.0f));
			legProfile.push_back(Vector3(0.01f, 0.1f, 0.0f));
			legProfile.push_back(Vector3(0.01f, 0.1f, 0.0f));
			return legProfile;
		}

}