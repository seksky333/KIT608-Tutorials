#include "BillboardTask.h"
#include "Billboard.h"


using namespace T3D;
namespace T3D
{
	BillboardTask::BillboardTask(T3DApplication* app) : Task(app) {


		elapsedTime = 0;
		gameObj = NULL;

	}

	void BillboardTask::update(float dt) {
		float t = 0;
		elapsedTime += dt;
		//t = elapsedTime / 5.0;


		if (elapsedTime < 5.0) {
			gameObj->setVisible(false);
			t = (elapsedTime - 0) / 5;
			//gameObj->transform->setLocalPosition(Vector3::lerp(Vector3(0, 0, 0), Vector3(1, 0, 0), t));
		}
		else if (elapsedTime < 10.0) {
			//total duration is 10 seconds, we want 1 at the end of that 10 seconds
			t = (elapsedTime - 5) / 5;
			//transform->setLocalPosition(Vector3::lerp(Vector3(1, 0, 0), Vector3(2, 0, 0), t));
		}
		else if (elapsedTime > 11.0 && elapsedTime < 14.0) {
			t = (elapsedTime - 10) / 5;
			gameObj->setVisible(true);
			//transform->setLocalPosition(Vector3::lerp(Vector3(2, 0, 0), Vector3(3, 0, 0), t));
		}
		else if (elapsedTime > 14.0 && elapsedTime < 15.0) {
			gameObj->setVisible(false);
		}
		else if (elapsedTime > 26.0 && elapsedTime < 29.0) {
			gameObj1->setVisible(true);
		}
		else if (elapsedTime > 29.0 && elapsedTime < 30.0) {
			gameObj1->setVisible(false);
		}
		else if (elapsedTime > 55.0 && elapsedTime < 59.0) {
			gameObj2->setVisible(true);
		}
		else if (elapsedTime > 59.0) {
			gameObj2->setVisible(false);
			gameObj3->setVisible(true);
		}
		else {
			//do nothing
		}



	}
}