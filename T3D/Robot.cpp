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
#include "Sweep.h"
#include "SweepPath.h"
#include "Robot.h"
#include "RobotHand.h"

namespace T3D
{
	Robot::Robot(T3DApplication* app) :GameObject(app) {
		{
			//head
			//setMesh(new Sphere(.1, 16*2));
			//getTransform()->name = "body";

			std::vector<Vector3> bodyProfile;
			bodyProfile.push_back(Vector3(-0.2f, -0.2f, 0.0f));
			//bodyProfile.push_back(Vector3(0.07f, -0.1f, 0.0f));
			//bodyProfile.push_back(Vector3(0.07f, -0.11f, 0.0f));
			//bodyProfile.push_back(Vector3(0.08f, -0.11f, 0.0f));
			//bodyProfile.push_back(Vector3(0.08f, -0.1f, 0.0f));
			bodyProfile.push_back(Vector3(0.2f, -0.2f, 0.0f));
			bodyProfile.push_back(Vector3(0.2f, 0.2f, 0.0f));
			bodyProfile.push_back(Vector3(-0.2f, 0.2f, 0.0f));

			//create the first transform
			t.setLocalPosition(Vector3(0, 0, 0));
			t.setLocalRotation(Quaternion(Vector3(0, Math::PI/2, 0)));
			//t.setLocalRotation(Quaternion(Vector3(0, 0, 0)));
			t.setLocalScale(Vector3(0.001, 0.001, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
			bodysp.addTransform(t);
			bodysp.addTransform(t);
			//Adjust the scale for the next path instance
			t.setLocalScale(Vector3(0.9, 1, 1.0));
			bodysp.addTransform(t);
			bodysp.addTransform(t);


			//Adjust the position for the next path instance
			t.setLocalPosition(Vector3(0.2, 0, 0));
			t.setLocalScale(Vector3(.9, 1, 1.0));
			bodysp.addTransform(t);
			bodysp.addTransform(t);

			//Adjust the scale for the final 'cap'
			t.setLocalScale(Vector3(0.001, 0.001, 1.0));
			bodysp.addTransform(t);
			bodysp.addTransform(t);

			body = new GameObject(app);
			body->setMesh(new Sweep(bodyProfile, bodysp, false));
			body->getTransform()->setLocalPosition(Vector3(-0.1, 0, 0)); // not correctly positioned yet
			//arm1->getTransform()->setLocalPosition(Vector3(0, 0.1, 0)); 
			body->getTransform()->setParent(getTransform()); // not correct attachment yet
			body->getTransform()->name = "Body";


			//body = new GameObject(app); // note the use of 'app' not 'this' - you should understand why
			//body->setMesh(new Cube(.15));
			//body->getTransform()->setParent(getTransform()); // attaching this piece to the Lamp object's transform
			//body->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			//body->getTransform()->name = "Body";

			////headJoint
			headJoint = new GameObject(app);
			headJoint->getTransform()->setParent(body->getTransform());
			headJoint->getTransform()->name = "HeadJoint";

			head = new GameObject(app); // note the use of 'app' not 'this' - you should understand why
			//head->setMesh(new Sphere(.1, 16 * 2));
			head->setMesh(new Cube(.07));
			head->getTransform()->setParent(headJoint->getTransform()); // attaching this piece to the Lamp object's transform
			head->getTransform()->setLocalPosition(Vector3(0.1, .26, 0));
			head->getTransform()->name = "Head";

			//leftHandJoint
			leftShoulderJoint= new GameObject(app);
			leftShoulderJoint->getTransform()->setLocalPosition(Vector3(0.1,0.125, 0.25));
			leftShoulderJoint->getTransform()->setParent(body->getTransform());
			leftShoulderJoint->getTransform()->name = "LeftHandJoint";

			leftShoulder = new GameObject(app); // note the use of 'app' not 'this' - you should understand why
			leftShoulder->setMesh(new Sphere(.07, 16 * 2));
			leftShoulder->getTransform()->setParent(leftShoulderJoint->getTransform()); // attaching this piece to the Lamp object's transform
			leftShoulder->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			leftShoulder->getTransform()->name = "LeftShoulder";
			
			//leftArmJoint
			leftArmJoint = new GameObject(app);
			leftArmJoint->getTransform()->setLocalPosition(Vector3(0.0, 0.0, 0.0));
			leftArmJoint->getTransform()->setParent(leftShoulder->getTransform());
			leftArmJoint->getTransform()->name = "leftArmJoint";

			std::vector<Vector3> leftArmProfile;
			//leftArmProfile.push_back(Vector3(0.0f, -0.1f, 0.0f));
			leftArmProfile.push_back(Vector3(0.04f, -0.1f, 0.0f));
			//leftArmProfile.push_back(Vector3(0.0f, -0.05f, 0.0f));
			leftArmProfile.push_back(Vector3(0.04f, -0.05f, 0.0f));
			//leftArmProfile.push_back(Vector3(0.0f, -0.0f, 0.0f));
			leftArmProfile.push_back(Vector3(0.04f, -0.0f, 0.0f));
			//leftArmProfile.push_back(Vector3(0.0f, 0.05f, 0.0f));
			leftArmProfile.push_back(Vector3(0.04f, 0.05f, 0.0f));
			//leftArmProfile.push_back(Vector3(0.0f, 0.1f, 0.0f));
			leftArmProfile.push_back(Vector3(0.04f, 0.1f, 0.0f));

	
			leftArmSP.makeCirclePath(0, 6 * 20);

			//lampShade attaches to shadeJoint
			leftArm = new GameObject(app);
			leftArm->setMesh(new Sweep(leftArmProfile, leftArmSP, false));
			leftArm->getTransform()->setLocalPosition(Vector3(0, -.15, 0));
			leftArm->getTransform()->setParent(leftArmJoint->getTransform());
			leftArm->getTransform()->name = "LeftArm";
			leftArmSP.addTransform(t);

			//leftHandJoint
			leftHandJoint = new GameObject(app);
			leftHandJoint->getTransform()->setLocalPosition(Vector3(0.0, -0.1, 0.0));
			leftHandJoint->getTransform()->setParent(leftArm->getTransform());
			leftHandJoint->getTransform()->name = "leftArmJoint";

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
			leftHandSP.addTransform(t);
			leftHandSP.addTransform(t);
			//Adjust the scale for the next path instance
			t.setLocalScale(Vector3(0.9, 1, 1.0));
			leftHandSP.addTransform(t);
			leftHandSP.addTransform(t);
			//Adjust the position and scale for the next path instance
			t.setLocalPosition(Vector3(-0.0075, 0, 0));
			t.setLocalScale(Vector3(1, 1, 1.0));
			leftHandSP.addTransform(t);
			leftHandSP.addTransform(t);
			//Adjust the position for the next path instance
			t.setLocalPosition(Vector3(0.0075, 0, 0));
			leftHandSP.addTransform(t);
			leftHandSP.addTransform(t);
			//Adjust the position for the next path instance
			t.setLocalPosition(Vector3(0.01, 0, 0));
			t.setLocalScale(Vector3(0.9, 1, 1.0));
			leftHandSP.addTransform(t);
			leftHandSP.addTransform(t);

			//Adjust the scale for the final 'cap'
			t.setLocalScale(Vector3(0.01, 0.01, 1.0));
			leftHandSP.addTransform(t);
			leftHandSP.addTransform(t);

			leftHand = new GameObject(app);
			leftHand->setMesh(new Sweep(robotHandProfile, leftHandSP, false));
			leftHand->getTransform()->setLocalPosition(Vector3(0, .1, 0)); // not correctly positioned yet
			leftHand->getTransform()->setParent(leftHandJoint->getTransform()); // not correct attachment yet
			leftHand->getTransform()->name = "Left Hand";
			leftHandSP.addTransform(t);

			//leftHand = new GameObject(app);
			//leftHand->setMesh(new RobotHand(app));
			//leftHand->getTransform()->setLocalPosition(Vector3(0, -.1, 0));
			//leftHand->getTransform()->setParent(leftHandJoint->getTransform());
			//leftHand->getTransform()->name = "LeftArm";
			//leftHandSP.addTransform(t);

		}
	}
}