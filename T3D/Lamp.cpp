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
#include "Sweep.h"
#include "SweepPath.h"


namespace T3D
{
	Lamp::Lamp(T3DApplication* app) :GameObject(app) {
		{
			setMesh(new Cylinder(.1, .01, 16));
			getTransform()->name = "Lamp";

			base = new GameObject(app); // note the use of 'app' not 'this' - you should understand why
			base->setMesh(new Cylinder(.02, .01, 16));
			base->getTransform()->setParent(getTransform()); // attaching this piece to the Lamp object's transform
			base->getTransform()->setLocalPosition(Vector3(0, 0.02, 0));
			base->getTransform()->name = "Base";

			//arm 1
			std::vector<Vector3> armProfile;
			armProfile.push_back(Vector3(0.0f, -0.12f, 0.0f));
			armProfile.push_back(Vector3(0.014f, -0.114f, 0.0f));
			armProfile.push_back(Vector3(0.02f, -0.1f, 0.0f));
			armProfile.push_back(Vector3(0.02f, 0.1f, 0.0f));
			armProfile.push_back(Vector3(0.014f, 0.114f, 0.0f));
			armProfile.push_back(Vector3(0.0f, 0.12f, 0.0f));
			armProfile.push_back(Vector3(-0.014f, 0.114f, 0.0f));
			armProfile.push_back(Vector3(-0.02f, 0.1f, 0.0f));
			armProfile.push_back(Vector3(-0.02f, -0.1f, 0.0f));
			armProfile.push_back(Vector3(-0.014f, -0.114f, 0.0f));
			//create the first transform
			t.setLocalPosition(Vector3(-0.01, 0, 0));
			t.setLocalRotation(Quaternion(Vector3(0, Math::PI / 2, 0)));
			t.setLocalScale(Vector3(0.01, 0.01, 1.0)); // no need to scale the z-direction because the profile is in the XY plane
			armsp.addTransform(t);
			armsp.addTransform(t);
			//Adjust the scale for the next path instance
			t.setLocalScale(Vector3(0.9, 1, 1.0));
			armsp.addTransform(t);
			armsp.addTransform(t);
			//Adjust the position and scale for the next path instance
			t.setLocalPosition(Vector3(-0.0075, 0, 0));
			t.setLocalScale(Vector3(1, 1, 1.0));
			armsp.addTransform(t);
			armsp.addTransform(t);
			//Adjust the position for the next path instance
			t.setLocalPosition(Vector3(0.0075, 0, 0));
			armsp.addTransform(t);
			armsp.addTransform(t);
			//Adjust the position for the next path instance
			t.setLocalPosition(Vector3(0.01, 0, 0));
			t.setLocalScale(Vector3(0.9, 1, 1.0));
			armsp.addTransform(t);
			armsp.addTransform(t);

			//Adjust the scale for the final 'cap'
			t.setLocalScale(Vector3(0.01, 0.01, 1.0));
			armsp.addTransform(t);
			armsp.addTransform(t);

			//arm1 = new GameObject(app);
			//arm1->setMesh(new Sweep(armProfile, armsp, false));
			//arm1->getTransform()->setLocalPosition(Vector3(0, 0.2, 0)); // not correctly positioned yet
			////arm1->getTransform()->setLocalPosition(Vector3(0, 0.1, 0)); 
			//arm1->getTransform()->setParent(base->getTransform()); // not correct attachment yet
			//arm1->getTransform()->name = "Arm1";



			////baseJoint
			baseJoint = new GameObject(app);
			baseJoint->getTransform()->setParent(base->getTransform());
			baseJoint->getTransform()->name = "BaseJoint";

			armsp.addTransform(t);

			////elbowJoint
			elbowJoint = new GameObject(app);
			elbowJoint->getTransform()->setLocalPosition(Vector3(0, 0.2, 0));
			elbowJoint->getTransform()->setParent(baseJoint->getTransform());
			elbowJoint->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 4, 0, 0))); // this rotation is just to make a good starting pose
			elbowJoint->getTransform()->name = "ElbowJoint";

			armsp.addTransform(t);
			////shadeJoint
			shadeJoint = new GameObject(app);
			shadeJoint->getTransform()->setLocalPosition(Vector3(0, 0.2, 0));
			shadeJoint->getTransform()->setParent(elbowJoint->getTransform());
			shadeJoint->getTransform()->name = "ShadeJoint";
			armsp.addTransform(t);

			//arm1 attaches to baseJoint with a 10cm offset in the y-direction 
			arm1 = new GameObject(app);
			arm1->setMesh(new Sweep(armProfile, armsp, false));
			arm1->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
			arm1->getTransform()->setParent(baseJoint->getTransform());
			arm1->getTransform()->name = "Arm1";

			arm2 = new GameObject(app);
			arm2->setMesh(new Sweep(armProfile, armsp, false));
			arm2->getTransform()->setLocalPosition(Vector3(0, 0.1, 0));
			arm2->getTransform()->setParent(elbowJoint->getTransform());
			arm2->getTransform()->name = "Arm2";

			//lampShade
			std::vector<Vector3> lampShadeProfile;
			lampShadeProfile.push_back(Vector3(0.0f, -0.07f, 0.0f));
			lampShadeProfile.push_back(Vector3(0.06f, -0.03f, 0.0f));
			lampShadeProfile.push_back(Vector3(0.085f, 0.06f, 0.0f));
			lampShadeProfile.push_back(Vector3(0.11f, 0.13f, 0.0f));
			//5
			lampShadeProfile.push_back(Vector3(0.14f, 0.19f, 0.0f));
			lampShadeProfile.push_back(Vector3(0.14f, 0.19f, 0.0f));
			//6
			lampShadeProfile.push_back(Vector3(0.13f, 0.2f, 0.0f));
			lampShadeProfile.push_back(Vector3(0.13f, 0.2f, 0.0f));

			lampShadeProfile.push_back(Vector3(0.085f, 0.14f, 0.0f));

			//8
			lampShadeProfile.push_back(Vector3(0.07f, 0.08f, 0.0f));
			lampShadeProfile.push_back(Vector3(0.07f, 0.08f, 0.0f));

			lampShadeProfile.push_back(Vector3(0.0f, 0.079f, 0.0f));
			
			
			//lampshadesp.makeCirclePath(0, 6*20);
			lampshadesp.makeCirclePath(0, 6 * 20);

			//lampShade attaches to shadeJoint
			lampShade = new GameObject(app);
			lampShade->setMesh(new Sweep(lampShadeProfile, lampshadesp, true));
			lampShade->getTransform()->setLocalPosition(Vector3(0, 0.05, 0));
			lampShade->getTransform()->setParent(shadeJoint->getTransform());
			lampShade->getTransform()->name = "lampShade";

			lampshadesp.addTransform(t);


			
		}
	}

}