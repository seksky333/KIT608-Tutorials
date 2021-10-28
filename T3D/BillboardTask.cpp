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


		if (elapsedTime > 8.0) {
			gameObj3->setVisible(true);
		}
		else {
			//do nothing
		}



	}
}