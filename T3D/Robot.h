#pragma once
#include "GameObject.h"
#include "SweepPath.h"
namespace T3D
{
	class Robot : public GameObject
	{
	public:
		Robot(T3DApplication* app);
		~Robot(void);
		std::vector<Vector3> getArmProfile();
		std::vector<Vector3> getHandProfile();
		std::vector<Vector3> getLegProfile();

		GameObject* body;
		GameObject* head;
		GameObject* headJoint;
		GameObject* leftShoulder;
		GameObject* leftArm;
		GameObject* leftHand;
		GameObject* rightShoulder;
		GameObject* rightArm;
		GameObject* rightHand;

		GameObject* leftEyeJoint;
		GameObject* leftEye;
		GameObject* rightEyeJoint;
		GameObject* rightEye;
		


		GameObject* leftShoulderJoint;
		GameObject* leftArmJoint;
		GameObject* leftHandJoint;

		GameObject* leftLegJoint;
		GameObject* leftLeg;
		GameObject* leftFootJoint;
		GameObject* leftFoot;

		GameObject* rightShoulderJoint;
		GameObject* rightArmJoint;
		GameObject* rightHandJoint;

		GameObject* rightLegJoint;
		GameObject* rightLeg;
		GameObject* rightFootJoint;
		GameObject* rightFoot;

		SweepPath bodysp;
		SweepPath leftArmSP;
		SweepPath leftHandSP;
		SweepPath rightArmSP;
		SweepPath rightHandSP;
		SweepPath leftLegSP;
		SweepPath rightLegSP;
		Transform t;
	};
}

