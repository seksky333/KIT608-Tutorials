#include "WineGlassTask.h"
#include "WineGlass.h"
#include "Animation.h"

using namespace T3D;
namespace T3D
{
	const float legJPosX = 0.0;
	const float legJPosY = -0.1425;
	const float legJPosZ = 0.10;

	WineGlassTask::WineGlassTask(T3DApplication* app) : Task(app) {
		elapsedTime = 0;
		gameObj = NULL;
	}

	void WineGlassTask::update(float dt) {
		float t = 0;
		elapsedTime += dt;
		//t = elapsedTime / 5.0;


		//std::string  debugText = "elapsedTime:" + std::to_string(elapsedTime);
		//printf("* Debug: %s \n", debugText.c_str());

		if (elapsedTime > 22.0 && elapsedTime < 23.0) {
			t = (elapsedTime - 22) / 1;
			gameObj->getTransform()->setLocalPosition(Vector3::lerp(Vector3(0, 0, 0), Vector3(1, 0, 0), t));
		}
		else if (elapsedTime > 23.0 && elapsedTime < 24.0) {
			t = (elapsedTime - 23) / 1;
			gameObj->getTransform()->setLocalPosition(Vector3::lerp(Vector3(1, 0, 0), Vector3(1, -1, 0), t));
		}
		else if (elapsedTime > 24.0 && elapsedTime < 25.0) {
			gameObj->setVisible(false);
		}
		else if (elapsedTime > 29.0 && elapsedTime < 30.0) {
			base->setVisible(false);
			leg1->setVisible(false);
			leg2->setVisible(false);
			leg3->setVisible(false);
			leg4->setVisible(false);
		}
		else {
			//do nothing
		}
	}

}