#pragma once
#include "GameObject.h"
#include "SweepPath.h"
namespace T3D
{

	class PhoneCase : public GameObject
	{
	public:
		PhoneCase(T3DApplication* app);
		~PhoneCase(void);

		GameObject* phoneCase;
		SweepPath phoneCaseSP;
		Transform t;

		GameObject* arm1;
		SweepPath armsp;
	};
}