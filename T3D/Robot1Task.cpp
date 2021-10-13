#include "Robot1Task.h"
#include "Robot.h"
#include "Animation.h"

using namespace T3D;
namespace T3D
{
	const float legJPosX = 0.0;
	const float legJPosY = -0.1425;
	const float legJPosZ = 0.10;

	Robot1Task::Robot1Task(T3DApplication* app) : Task(app) {
		elapsedTime = 0;
		gameObj = NULL;
	}

	void Robot1Task::update(float dt) {
		float t = 0;
		elapsedTime += dt;
		//t = elapsedTime / 5.0;

		Animation* walkingAnime = new Animation(10.0);
		gameObj->addComponent(walkingAnime);

		walkingAnime->addKey("RightLegJoint", 0, Quaternion(Vector3(legJPosX, legJPosY, -legJPosZ)), Vector3(legJPosX, legJPosY, -legJPosZ));
		addRobotWalking("RightLegJoint", 1, 9, walkingAnime);
		walkingAnime->addKey("RightLegJoint", 10.0, Quaternion(Vector3(legJPosX, legJPosY, -legJPosZ)), Vector3(legJPosX, legJPosY, -legJPosZ));

		walkingAnime->addKey("LeftLegJoint", 0, Quaternion(Vector3(legJPosX, legJPosY, legJPosZ)), Vector3(legJPosX, legJPosY, legJPosZ));
		addRobotWalking("LeftLegJoint", 1, 9, walkingAnime);
		walkingAnime->addKey("LeftLegJoint", 10.0, Quaternion(Vector3(legJPosX, legJPosY, legJPosZ)), Vector3(legJPosX, legJPosY, legJPosZ));


		//< 5
		if (elapsedTime < 5.0) {
			//if (!isWalking) {
			//	walkingAnime->play();
			//	isWalking = true;
			//}
			t = (elapsedTime - 0) / 5;
			gameObj->getTransform()->setLocalPosition(Vector3::lerp(Vector3(0, 0, 0), Vector3(1, 0, 0), t));
		}
		// 5 - 10
		else if (elapsedTime < 10.0) {
			//if (isWalking) {
			//	walkingAnime->pause();
			//	isWalking = false;
			//}

			//total duration is 10 seconds, we want 1 at the end of that 10 seconds
			t = (elapsedTime - 5) / 5;
			gameObj->getTransform()->setLocalPosition(Vector3::lerp(Vector3(1, 0, 0), Vector3(2, 0, 0), t));
		}
		// 10 - 15
		else if (elapsedTime < 15.0) {
			t = (elapsedTime - 10) / 5;
			gameObj->getTransform()->setLocalPosition(Vector3::lerp(Vector3(2, 0, 0), Vector3(3, 0, 0), t));
		}
		else {
			//do nothing
			elapsedTime = 0.0;
		}
	}

	void Robot1Task::addRobotWalking(std::string element, int startFramePos, int endFramePos, Animation* anim) {
		float framePos = 0.0;
		for (int i = 1; i < 9; i++) {
			framePos = i;
			//if leftLeg
			if (element == "LeftLegJoint") {
				if (i % 2 == 0) {
					anim->addKey(element, framePos, Quaternion(Vector3(legJPosX, legJPosY, legJPosZ - Math::HALF_PI / 3.5)), Vector3(legJPosX, legJPosY, legJPosZ));
				}
				else {
					anim->addKey(element, framePos, Quaternion(Vector3(legJPosX, legJPosY, Math::HALF_PI / 3.5)), Vector3(legJPosX, legJPosY, legJPosZ));
				}
			}
			//if righttLeg
			else {
				if (i % 2 == 0) {
					anim->addKey(element, framePos, Quaternion(Vector3(legJPosX, legJPosY, Math::HALF_PI / 3.5)), Vector3(legJPosX, legJPosY, -legJPosZ));
				}
				else {
					anim->addKey(element, framePos, Quaternion(Vector3(legJPosX, legJPosY, -legJPosZ - Math::HALF_PI / 3.5)), Vector3(legJPosX, legJPosY, -legJPosZ));
				}
			}

		}
	}
}