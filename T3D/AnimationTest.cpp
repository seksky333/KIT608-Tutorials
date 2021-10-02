#include "AnimationTest.h"
#include "Lamp.h"

using namespace T3D;
namespace T3D
{
	AnimationTest::AnimationTest(T3DApplication* app) : Task(app){

		elapsedTime = 0;
		lampTransform = NULL;
		
	}

	void AnimationTest::update(float dt) {
		float t = 0;
		elapsedTime += dt;
		//t = elapsedTime / 5.0;


		if (elapsedTime < 5.0) {
			t = (elapsedTime - 0) / 5;
			lampTransform->setLocalPosition(Vector3::lerp(Vector3(0, 0, 0), Vector3(0, 0, 1), t));
		}else if (elapsedTime < 10.0) {
			//total duration is 10 seconds, we want 1 at the end of that 10 seconds
			t = (elapsedTime - 5) / 5;
			lampTransform->setLocalPosition(Vector3::lerp(Vector3(0, 0, 1), Vector3(0, 0, 2), t));
		}
		else if (elapsedTime < 15.0) {
			t = (elapsedTime - 10) / 5;
			lampTransform->setLocalPosition(Vector3::lerp(Vector3(0, 0, 2), Vector3(0, 0, 3), t));
		}
		else {
			//do nothing
			elapsedTime = 0.0;
		}

		
		
	}
}