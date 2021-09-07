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

		GameObject* body;
		GameObject* head;
		GameObject* leftShoulder;
		GameObject* leftArm;
		GameObject* leftHand;
		GameObject* rightShoulder;

		GameObject* headJoint;

		GameObject* leftShoulderJoint;
		GameObject* leftArmJoint;
		GameObject* leftHandJoint;

		GameObject* rightHandJoint;

		SweepPath bodysp;
		SweepPath leftArmSP;
		SweepPath leftHandSP;
		Transform t;
	};
}

