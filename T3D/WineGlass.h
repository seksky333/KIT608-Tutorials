#pragma once
#include "GameObject.h"
#include "SweepPath.h"
namespace T3D
{

	class WineGlass : public GameObject
	{
	public:
		WineGlass(T3DApplication* app);
		~WineGlass(void);

		GameObject* wineGlass;
		SweepPath wineGlassSP;
		Transform t;

	};
}
