#pragma once
#include "GameObject.h"
#include "SweepPath.h"
namespace T3D
{
		class TableWithGlass : public GameObject
	{
	public:
		TableWithGlass(T3DApplication* app, float length, float width, float height, int wineGlassPos);
		std::vector<Vector3> getWineGlassProfile();
		Vector3 getWineGlassLocation(float legXPos, float legZPos, int desiredPos);

		GameObject* base;
		GameObject* leg1;
		GameObject* leg2;
		GameObject* leg3;
		GameObject* leg4;
		GameObject* wineGlass;

		GameObject* leg1Joint;
		GameObject* leg2Joint;
		GameObject* leg3Joint;
		GameObject* leg4Joint;
		GameObject* wineGlassLocation;

		SweepPath wineGlassSP;
		Transform t;
	};

}