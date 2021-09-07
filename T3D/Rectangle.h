#pragma once
#include "GameObject.h"
#include "SweepPath.h"
namespace T3D
{

	class Rectangle : public GameObject
	{
	public:
		Rectangle(T3DApplication* app);
		~Rectangle(void);

		GameObject* phoneCase;
		SweepPath phoneCaseSP;
		Transform t;

		GameObject* arm1;
		SweepPath armsp;
	};
}