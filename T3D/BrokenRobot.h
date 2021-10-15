
#pragma once
#include "GameObject.h"
#include "SweepPath.h"
namespace T3D
{
	class BrokenRobot : public GameObject
	{
	public:
		BrokenRobot(T3DApplication* app);
		~BrokenRobot(void);

		GameObject* base;
		GameObject* arm1;
		GameObject* arm2;
		GameObject* lampShade;
		GameObject* baseJoint;
		GameObject* elbowJoint;
		GameObject* shadeJoint;
		SweepPath armsp;
		SweepPath lampshadesp;
		Transform t;
	};
}

