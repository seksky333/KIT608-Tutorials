#include "TableWithGlass.h"
#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include "Component.h"
#include "Transform.h"
#include "GLRenderer.h"
#include "KeyboardController.h"
#include "Input.h"
#include "Math.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Cylinder.h"
#include "Rectangle.h"
#include "WineGlass.h"
#include "Cylinder.h"
#include "Sweep.h"
#include "SweepPath.h"

namespace T3D
{
	TableWithGlass::TableWithGlass(T3DApplication* app, float length, float width, float height, int wineGlassPos) :GameObject(app) {
		{


			const float tableLength= length;
			const float tableWidth= width;
			const float tableHeight = height;

			const float tableBaseHeight = tableHeight *.1;
			const float tableLegHeight = tableHeight *.9;
			
			const float tableWineGlassY = tableHeight * .8;

			const float tableLegRadius = .05;

			const int wineGlassDesiredLocation = wineGlassPos;

			const float legXPos = tableLength * .9;
			const float legYPos = tableLegHeight;
			const float legZPos = tableWidth * .8;

			base = new GameObject(app);
			base->setMesh(new Rectangle(Vector3(tableLength, tableBaseHeight, tableWidth)));
			base->getTransform()->setParent(getTransform()); // attaching this piece to the Lamp object's transform
			base->getTransform()->setLocalPosition(Vector3(0, 0.02, 0));
			base->getTransform()->name = "Base";

			leg1Joint = new GameObject(app);
			leg1Joint->getTransform()->setLocalPosition(Vector3(-legXPos, -legYPos, -legZPos));
			leg1Joint->getTransform()->setParent(base->getTransform());
			leg1Joint->getTransform()->name = "Leg1Joint";

			leg1= new GameObject(app);
			leg1->setMesh(new Cylinder(tableLegRadius, tableLegHeight,6*4));
			leg1->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			leg1->getTransform()->setParent(leg1Joint->getTransform());
			leg1->getTransform()->name = "Leg1";

			leg2Joint = new GameObject(app);
			leg2Joint->getTransform()->setLocalPosition(Vector3(-legXPos, -legYPos, legZPos));
			leg2Joint->getTransform()->setParent(base->getTransform());
			leg2Joint->getTransform()->name = "Leg2Joint";

			leg2 = new GameObject(app);
			leg2->setMesh(new Cylinder(tableLegRadius, tableLegHeight, 6 * 4));
			leg2->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			leg2->getTransform()->setParent(leg2Joint->getTransform());
			leg2->getTransform()->name = "Leg2";

			leg3Joint = new GameObject(app);
			leg3Joint->getTransform()->setLocalPosition(Vector3(legXPos, -legYPos, -legZPos));
			leg3Joint->getTransform()->setParent(base->getTransform());
			leg3Joint->getTransform()->name = "Leg3Joint";

			leg3 = new GameObject(app);
			leg3->setMesh(new Cylinder(tableLegRadius, tableLegHeight, 6 * 4));
			leg3->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			leg3->getTransform()->setParent(leg3Joint->getTransform());
			leg3->getTransform()->name = "Leg3";

			leg4Joint = new GameObject(app);
			leg4Joint->getTransform()->setLocalPosition(Vector3(legXPos, -legYPos, legZPos));
			leg4Joint->getTransform()->setParent(base->getTransform());
			leg4Joint->getTransform()->name = "Leg4Joint";

			leg4 = new GameObject(app);
			leg4->setMesh(new Cylinder(tableLegRadius, tableLegHeight, 6 * 4));
			leg4->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			leg4->getTransform()->setParent(leg4Joint->getTransform());
			leg4->getTransform()->name = "Leg4";

			Vector3 wineGlassDesiredPosition = getWineGlassLocation(legXPos, legZPos, wineGlassDesiredLocation);
			wineGlassLocation = new GameObject(app);
			wineGlassLocation->getTransform()->setLocalPosition(Vector3(wineGlassDesiredPosition.x, tableWineGlassY, wineGlassDesiredPosition.z));
			wineGlassLocation->getTransform()->setParent(base->getTransform());
			wineGlassLocation->getTransform()->name = "WineGlassLocation";

			//wineGlass
			std::vector<Vector3> wineGlassProfile = getWineGlassProfile();

			wineGlassSP.makeCirclePath(0, 6 * 20);

			wineGlass = new GameObject(app);
			wineGlass->setMesh(new Sweep(wineGlassProfile, wineGlassSP, true));
			wineGlass->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			wineGlass->getTransform()->setParent(wineGlassLocation->getTransform());
			wineGlass->getTransform()->name = "WineGlass";
			wineGlassSP.addTransform(t);
		}
	}
	Vector3 TableWithGlass::getWineGlassLocation(float legXPos, float legZPos, int desiredPos) {
		switch (desiredPos) {
		case 0:
			//leg joint1
			return Vector3(-legXPos, 0, -legZPos);
		case 1:
			//leg joint2
			return Vector3(-legXPos, 0, legZPos);
		case 2:
			//leg joint3
			return Vector3(legXPos, 0, -legZPos);
		case 3:
			//leg joint4
			return Vector3(legXPos, 0, legZPos);
		}
	}

	std::vector<Vector3> TableWithGlass::getWineGlassProfile() {
		std::vector<Vector3> profile;
		profile.push_back(Vector3(0.0f, -0.2f, 0.0f));
		profile.push_back(Vector3(0.1f, -0.2f, 0.0f));
		//3
		profile.push_back(Vector3(0.01f, -0.15f, 0.0f));
		//4
		profile.push_back(Vector3(0.01f, -0.05f, 0.0f));
		//5
		profile.push_back(Vector3(0.1f, 0.0f, 0.0f));
		profile.push_back(Vector3(0.1f, 0.0f, 0.0f));
		//6
		profile.push_back(Vector3(0.11f, 0.1f, 0.0f));
		profile.push_back(Vector3(0.12f, 0.2f, 0.0f));
		profile.push_back(Vector3(0.12f, 0.2f, 0.0f));

		//8
		profile.push_back(Vector3(0.115f, 0.2f, 0.0f));
		profile.push_back(Vector3(0.115f, 0.2f, 0.0f));

		profile.push_back(Vector3(0.105f, 0.1f, 0.0f));
		//10
		profile.push_back(Vector3(0.095f, 0.0f, 0.0f));
		profile.push_back(Vector3(0.0f, 0.0f, 0.0f));
		return profile;
	}
}