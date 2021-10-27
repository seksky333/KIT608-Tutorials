#pragma once
#include "GameObject.h"
#include "SweepPath.h"
namespace T3D
{

	class SpoonBody : public GameObject
	{
	public:
		SpoonBody(T3DApplication* app);

		GameObject* spoonBody;
		SweepPath spoonBodySP;
		Transform t;

	};

}
