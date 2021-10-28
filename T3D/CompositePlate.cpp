#include "CompositePlate.h"
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
	CompositePlate::CompositePlate(T3DApplication* app) :GameObject(app) {
		{
			plate = new GameObject(app);
			plate->setMesh(new Plate(.5,0.005, 24));
			plate->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			plate->getTransform()->setParent(getTransform());
			plate->getTransform()->name = "plate";

			plate->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 2, Math::PI / 2, 0)));

			//leftEyeJoint
			leftEyeJoint = new GameObject(app);
			leftEyeJoint->getTransform()->setLocalPosition(Vector3(-0.17, 0.03, -0.1));
			leftEyeJoint->getTransform()->setParent(plate->getTransform());
			leftEyeJoint->getTransform()->name = "LeftEyeJoint";

			leftEye = new GameObject(app); // note the use of 'app' not 'this' - you should understand why
			leftEye->setMesh(new Sphere(0.035, 16 * 2));
			leftEye->getTransform()->setParent(leftEyeJoint->getTransform()); // attaching this piece to the Lamp object's transform
			leftEye->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			leftEye->getTransform()->name = "LeftEye";

			//rightEyeJoint
			rightEyeJoint = new GameObject(app);
			rightEyeJoint->getTransform()->setLocalPosition(Vector3(0.17, 0.03, -0.1));
			rightEyeJoint->getTransform()->setParent(plate->getTransform());
			rightEyeJoint->getTransform()->name = "RightEyeJoint";

			rightEye = new GameObject(app); // note the use of 'app' not 'this' - you should understand why
			rightEye->setMesh(new Sphere(0.035, 16 * 2));
			rightEye->getTransform()->setParent(rightEyeJoint->getTransform()); // attaching this piece to the Lamp object's transform
			rightEye->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			rightEye->getTransform()->name = "RightEye";

			//rightShoulderJoint
			rightShoulderJoint = new GameObject(app);
			rightShoulderJoint->getTransform()->setLocalPosition(Vector3(-0.55, 0.0, -0.10));
			rightShoulderJoint->getTransform()->setParent(plate->getTransform());
			rightShoulderJoint->getTransform()->name = "RightHandJoint";

			

			rightShoulder = new GameObject(app); // note the use of 'app' not 'this' - you should understand why
			rightShoulder->setMesh(new Sphere(.07, 16 * 2));
			rightShoulder->getTransform()->setParent(rightShoulderJoint->getTransform()); // attaching this piece to the Lamp object's transform
			rightShoulder->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			rightShoulder->getTransform()->name = "RightShoulder";

			//rightArmJoint
			rightArmJoint = new GameObject(app);
			rightArmJoint->getTransform()->setLocalPosition(Vector3(0.0, 0.0, 0.0));
			rightArmJoint->getTransform()->setParent(rightShoulder->getTransform());
			rightArmJoint->getTransform()->name = "rightArmJoint";

			std::vector<Vector3> rightArmProfile;
			rightArmProfile = getArmProfile();
			rightArmSP.makeCirclePath(0, 6 * 20);

			rightArm = new GameObject(app);
			rightArm->setMesh(new Sweep(rightArmProfile, rightArmSP, true));
			rightArm->getTransform()->setLocalPosition(Vector3(0, -.15, 0));
			rightArm->getTransform()->setParent(rightArmJoint->getTransform());
			rightArm->getTransform()->name = "RightArm";
			rightArmSP.addTransform(t);

			//rightHandJoint
			rightHandJoint = new GameObject(app);
			rightHandJoint->getTransform()->setLocalPosition(Vector3(0.0, -0.1, 0.0));
			rightHandJoint->getTransform()->setParent(rightArm->getTransform());
			rightHandJoint->getTransform()->name = "rightHandJoint";

			
			std::vector<Vector3> rightHandProfile;
			rightHandProfile = getHandProfile();

			//create the first transform
			t.setLocalPosition(Vector3(-0.01, 0, 0.0));
			t.setLocalRotation(Quaternion(Vector3(0, Math::PI / 2, 0)));
			t.setLocalScale(Vector3(0.01, 0.01, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
			rightHandSP.addTransform(t);
			rightHandSP.addTransform(t);
			//Adjust the scale for the next path instance
			t.setLocalScale(Vector3(0.9, 1, 1.0));
			rightHandSP.addTransform(t);
			rightHandSP.addTransform(t);
			//Adjust the position and scale for the next path instance
			t.setLocalPosition(Vector3(-0.0075, 0, 0));
			t.setLocalScale(Vector3(1, 1, 1.0));
			rightHandSP.addTransform(t);
			rightHandSP.addTransform(t);
			//Adjust the position for the next path instance
			t.setLocalPosition(Vector3(0.0075, 0, 0));
			rightHandSP.addTransform(t);
			rightHandSP.addTransform(t);
			//Adjust the position for the next path instance
			t.setLocalPosition(Vector3(0.01, 0, 0));
			t.setLocalScale(Vector3(0.9, 1, 1.0));
			rightHandSP.addTransform(t);
			rightHandSP.addTransform(t);

			//Adjust the scale for the final 'cap'
			t.setLocalScale(Vector3(0.01, 0.01, 1.0));
			rightHandSP.addTransform(t);
			rightHandSP.addTransform(t);

			rightHand = new GameObject(app);
			rightHand->setMesh(new Sweep(rightHandProfile, rightHandSP, false));
			rightHand->getTransform()->setLocalPosition(Vector3(0, .1, 0)); // not correctly positioned yet
			rightHand->getTransform()->setParent(rightHandJoint->getTransform()); // not correct attachment yet
			rightHand->getTransform()->name = "RightHand";
			rightHandSP.addTransform(t);


			//leftShoulderJoint
			leftShoulderJoint = new GameObject(app);
			leftShoulderJoint->getTransform()->setLocalPosition(Vector3(0.55, 0.0, -0.10));
			leftShoulderJoint->getTransform()->setParent(plate->getTransform());
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
			leftArmProfile = getArmProfile();
			leftArmSP.makeCirclePath(0, 6 * 20);

			leftArm = new GameObject(app);
			leftArm->setMesh(new Sweep(leftArmProfile, leftArmSP, true));
			leftArm->getTransform()->setLocalPosition(Vector3(0, -.15, 0));
			leftArm->getTransform()->setParent(leftArmJoint->getTransform());
			leftArm->getTransform()->name = "LeftArm";
			leftArmSP.addTransform(t);

			//leftHandJoint
			leftHandJoint = new GameObject(app);
			leftHandJoint->getTransform()->setLocalPosition(Vector3(0.0, -0.1, 0.0));
			leftHandJoint->getTransform()->setParent(leftArm->getTransform());
			leftHandJoint->getTransform()->name = "leftHandJoint";

			std::vector<Vector3> leftHandProfile;
			leftHandProfile = getHandProfile();

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
			leftHand->setMesh(new Sweep(leftHandProfile, leftHandSP, false));
			leftHand->getTransform()->setLocalPosition(Vector3(0, .1, 0)); // not correctly positioned yet
			leftHand->getTransform()->setParent(leftHandJoint->getTransform()); // not correct attachment yet
			leftHand->getTransform()->name = "LeftHand";
			leftHandSP.addTransform(t);

			/*
			Hands rotation configurations*/
			rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 2, 0, 0)));
			leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 2, 0, 0)));
			rightHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI, Math::PI / 2, 0)));
			leftHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI, Math::PI / 2, 0)));

			//rightLegJoint
			rightLegJoint = new GameObject(app);
			rightLegJoint->getTransform()->setLocalPosition(Vector3(-0.20, -0.011, 0.4));
			rightLegJoint->getTransform()->setParent(plate->getTransform());
			rightLegJoint->getTransform()->name = "RightLegJoint";

			std::vector<Vector3> rightLegProfile;
			rightLegProfile = getLegProfile();
			rightLegSP.makeCirclePath(.02, 6 * 20);

			rightLeg = new GameObject(app);
			rightLeg->setMesh(new Sweep(rightLegProfile, rightLegSP, true));
			rightLeg->getTransform()->setLocalPosition(Vector3(0, -.15, 0));
			rightLeg->getTransform()->setParent(rightLegJoint->getTransform());
			rightLeg->getTransform()->name = "RightLeg";
			rightLegSP.addTransform(t);

			//rightFootJoint
			rightFootJoint = new GameObject(app);
			rightFootJoint->getTransform()->setLocalPosition(Vector3(0.0, -0.1, 0.0));
			rightFootJoint->getTransform()->setParent(rightLeg->getTransform());
			rightFootJoint->getTransform()->name = "RightFootJoint";

			rightFoot = new GameObject(app);
			rightFoot->setMesh(new Rectangle(Vector3(.09, .05, .09)));
			rightFoot->getTransform()->setParent(rightFootJoint->getTransform()); // attaching this piece to the Lamp object's transform
			rightFoot->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			rightFoot->getTransform()->name = "RightFoot";

			//leftLegJoint
			leftLegJoint = new GameObject(app);
			leftLegJoint->getTransform()->setLocalPosition(Vector3(0.20, -0.011, 0.4));
			leftLegJoint->getTransform()->setParent(plate->getTransform());
			leftLegJoint->getTransform()->name = "LeftLegJoint";

			std::vector<Vector3> leftLegProfile;
			leftLegProfile = getLegProfile();
			leftLegSP.makeCirclePath(.02, 6 * 20);

			leftLeg = new GameObject(app);
			leftLeg->setMesh(new Sweep(leftLegProfile, leftLegSP, true));
			leftLeg->getTransform()->setLocalPosition(Vector3(0, -.15, 0));
			leftLeg->getTransform()->setParent(leftLegJoint->getTransform());
			leftLeg->getTransform()->name = "LeftLeg";
			leftLegSP.addTransform(t);

			//leftFootJoint
			leftFootJoint = new GameObject(app);
			leftFootJoint->getTransform()->setLocalPosition(Vector3(0.0, -0.1, 0.0));
			leftFootJoint->getTransform()->setParent(leftLeg->getTransform());
			leftFootJoint->getTransform()->name = "LeftFootJoint";

			leftFoot = new GameObject(app);
			leftFoot->setMesh(new Rectangle(Vector3(.09, .05, .09)));
			leftFoot->getTransform()->setParent(leftFootJoint->getTransform()); // attaching this piece to the Lamp object's transform
			leftFoot->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			leftFoot->getTransform()->name = "LeftFoot";

			/*Legs rotation configurations*/
			rightLegJoint->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 2, 0, 0)));
			leftLegJoint->getTransform()->setLocalRotation(Quaternion(Vector3(-Math::PI / 2, 0, 0)));

		}

	}
	std::vector<Vector3> CompositePlate::getLegProfile() {
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

	std::vector<Vector3> CompositePlate::getArmProfile() {
		std::vector<Vector3> armProfile;
		//leftArmProfile.push_back(Vector3(0.0f, -0.1f, 0.0f));
		armProfile.push_back(Vector3(0.04f, -0.1f, 0.0f));
		armProfile.push_back(Vector3(0.04f, -0.1f, 0.0f));
		//leftArmProfile.push_back(Vector3(0.0f, -0.05f, 0.0f));
		armProfile.push_back(Vector3(0.04f, -0.05f, 0.0f));
		//leftArmProfile.push_back(Vector3(0.0f, -0.0f, 0.0f));
		armProfile.push_back(Vector3(0.04f, -0.0f, 0.0f));
		//leftArmProfile.push_back(Vector3(0.0f, 0.05f, 0.0f));
		armProfile.push_back(Vector3(0.04f, 0.05f, 0.0f));
		//leftArmProfile.push_back(Vector3(0.0f, 0.1f, 0.0f));
		armProfile.push_back(Vector3(0.04f, 0.1f, 0.0f));
		armProfile.push_back(Vector3(0.04f, 0.1f, 0.0f));
		return armProfile;
	}

	std::vector<Vector3> CompositePlate::getHandProfile() {
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
		return robotHandProfile;
	}
}