#include "WineGlass.h"

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
#include "Sweep.h"
#include "SweepPath.h"


namespace T3D
{
	WineGlass::WineGlass(T3DApplication* app) :GameObject(app) {
		{
			//wineGlass
			std::vector<Vector3> wineGlassProfile;
			wineGlassProfile.push_back(Vector3(0.0f, -0.2f, 0.0f));
			wineGlassProfile.push_back(Vector3(0.1f, -0.2f, 0.0f));
			//3
			wineGlassProfile.push_back(Vector3(0.01f, -0.15f, 0.0f));
			//4
			wineGlassProfile.push_back(Vector3(0.01f, -0.05f, 0.0f));
			//5
			wineGlassProfile.push_back(Vector3(0.1f, 0.0f, 0.0f));
			wineGlassProfile.push_back(Vector3(0.1f, 0.0f, 0.0f));
			//6
			wineGlassProfile.push_back(Vector3(0.11f, 0.1f, 0.0f));
			wineGlassProfile.push_back(Vector3(0.12f, 0.2f, 0.0f));
			wineGlassProfile.push_back(Vector3(0.12f, 0.2f, 0.0f));

			//8
			wineGlassProfile.push_back(Vector3(0.115f, 0.2f, 0.0f));
			wineGlassProfile.push_back(Vector3(0.115f, 0.2f, 0.0f));

			wineGlassProfile.push_back(Vector3(0.105f, 0.1f, 0.0f));
			//10
			wineGlassProfile.push_back(Vector3(0.095f, 0.0f, 0.0f));
			wineGlassProfile.push_back(Vector3(0.0f, 0.0f, 0.0f));

			//lampshadesp.makeCirclePath(0, 6*20);
			wineGlassSP.makeCirclePath(0, 6 * 20);
			//wineGlassSP.makeCirclePath(0, 3);

			//lampShade attaches to shadeJoint
			wineGlass = new GameObject(app);
			wineGlass->setMesh(new Sweep(wineGlassProfile, wineGlassSP, true));
			wineGlass->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			wineGlass->getTransform()->setParent(getTransform());
			wineGlass->getTransform()->name = "wineGlass";
			wineGlassSP.addTransform(t);
		}
	}


}