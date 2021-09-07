#pragma once
#include "GameObject.h"
#include "SweepPath.h"
namespace T3D {
	class RobotHand : public GameObject
	{
	public:
		RobotHand(T3DApplication* app);
		~RobotHand(void);

		GameObject* robotHand;

		SweepPath robotHandSP;
		Transform t;
	};
}