#include "CameraTask.h"
#include "Animation.h"
#include "GameObject.h"
#include "LookAtBehaviour.h"
using namespace T3D;
namespace T3D
{
	CameraTask::CameraTask(T3DApplication* app) : Task(app) {
		elapsedTime = 0;
		camObj = NULL;
	}

	void CameraTask::update(float dt) {
		float t = 0;
		elapsedTime += dt;
		//< 5
		if (elapsedTime < 5.0) {
			//if (!isWalking) {
			//	walkingAnime->play();
			//	isWalking = true;
			//}
			t = (elapsedTime - 0) / 5;
			/*gameObj->getTransform()->setLocalRotation(Quaternion(Vector3(0, Math::PI/2 , 0)));*/
			//gameObj->getTransform()->setLocalPosition(Vector3::lerp(Vector3(0, 0, 0), Vector3(1, 0, 0), t));
		}
		else if (elapsedTime < 10.0) {
			//if (isWalking) {
			//	walkingAnime->pause();
			//	isWalking = false;
			//}
			camObj->getTransform()->setLocalRotation(Quaternion(Vector3((Math::PI / 100) * 15, Math::PI, 0)));


			//total duration is 10 seconds, we want 1 at the end of that 10 seconds
			t = (elapsedTime - 5) / 5;
			//gameObj->getTransform()->setLocalPosition(Vector3::lerp(Vector3(1, 0, 0), Vector3(2, 0, 0), t));
		}
		else if (elapsedTime < 15.0) {
			camObj->getTransform()->setLocalRotation(Quaternion(Vector3(Math::PI / 100, Math::PI / 2, 0)));
		}
		else {

		}
	}
}