#pragma once
#include "GameObject.h"
#include "SweepPath.h"
namespace T3D
{
	class Lamp: public GameObject
	{
	public:
		Lamp(T3DApplication* app);
		~Lamp(void);

		GameObject* base;
		GameObject* arm1;
		GameObject* arm2;
		GameObject* lampShade;
		GameObject* baseJoint;
		GameObject* elbowJoint;
		GameObject* shadeJoint;
		SweepPath armsp;
		Transform t;
	};
}

