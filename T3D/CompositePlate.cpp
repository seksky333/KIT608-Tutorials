#include "CompositePlate.h"
#include "Lamp.h"
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
#include "Sphere.h"
#include "Rectangle.h"
#include "Sweep.h"
#include "SweepPath.h"
#include "Spoon.h"
#include "RobotHand.h"

namespace T3D
{
	CompositePlate::CompositePlate(T3DApplication* app) :GameObject(app) {
		{
			plate = new GameObject(app);
			plate->setMesh(new Plate(1, .05, 24));
			plate->getTransform()->setLocalPosition(Vector3(0, 0, 0));
			plate->getTransform()->setParent(getTransform());
			plate->getTransform()->name = "plate";

			plate->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 2, Math::PI / 2, 0)));
		}

	}
	std::vector<Vector3> CompositePlate::getLegProfile() {
		std::vector<Vector3> legProfile;
		legProfile.push_back(Vector3(0.01f, -0.1f, 0.0f));
		legProfile.push_back(Vector3(0.01f, -0.1f, 0.0f));
		legProfile.push_back(Vector3(0.01f, -0.05f, 0.0f));
		legProfile.push_back(Vector3(0.01f, -0.0f, 0.0f));
		legProfile.push_back(Vector3(0.01f, 0.05f, 0.0f));
		legProfile.push_back(Vector3(0.01f, 0.1f, 0.0f));
		legProfile.push_back(Vector3(0.01f, 0.1f, 0.0f));
		return legProfile;
	}

}