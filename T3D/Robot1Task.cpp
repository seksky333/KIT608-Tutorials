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
		robot = NULL;
	}

	void Robot1Task::update(float dt) {
		float t = 0;
		elapsedTime += dt;
		//t = elapsedTime / 5.0;

		Animation* walkingAnime = new Animation(60.0);
		robot->addComponent(walkingAnime);

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
			//t = (elapsedTime - 0) / 5;
			//robot->getTransform()->setLocalPosition(Vector3::lerp(Vector3(0, 0, 0), Vector3(1, 0, 0), t));
		}
		// 5 - 10
		else if (elapsedTime > 10.0 && elapsedTime < 12.0) {
			//testing
			/*t = (elapsedTime - 10) /2;
			robot->leftHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(Math::PI, Math::PI / 2, 0), Vector3(Math::PI, Math::TWO_PI, 0), t)));*/

			//face right
			//robot->body->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, Math::PI - (Math::PI / 4), 0), Vector3(0,  Math::PI, 0), t)));

			//face front
			//robot->body->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, Math::PI, 0), Vector3(0,  Math::PI/2.5, 0), t)));
			//face right
			/*robot->body->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, Math::PI / 2.5, 0), Vector3(0, Math::PI, 0), t)));*/

			//total duration is 10 seconds, we want 1 at the end of that 10 seconds
			//t = (elapsedTime - 5) / 5;
			//robot->getTransform()->setLocalPosition(Vector3::lerp(Vector3(1, 0, 0), Vector3(2, 0, 0), t));
		}
		// 10 - 15
		else if (elapsedTime < 15.0) {
			//t = (elapsedTime - 10) / 5;
			//robot->getTransform()->setLocalPosition(Vector3::lerp(Vector3(2, 0, 0), Vector3(3, 0, 0), t));
		}
		else if (elapsedTime > 30.0 && elapsedTime < 32.0) {
			if (!isWalking) {
				walkingAnime->play();
				isWalking = true;
			}
			t = (elapsedTime - 30) / 2;
			//face front
			robot->body->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, Math::PI - (Math::PI / 4), 0), Vector3(0,  Math::PI/2.5, 0), t)));
		}
		else if (elapsedTime > 32.0 && elapsedTime < 34.0) {
			t = (elapsedTime - 32) / 2;
			robot->getTransform()->setLocalPosition(Vector3::lerp(Vector3(0, 0, 1), Vector3(.8, 0, 1), t));
		}
		else if (elapsedTime > 34.0 && elapsedTime < 36.0) {
			if (elapsedTime > 35.90) {
				if (isWalking) {
					walkingAnime->pause();
					isWalking = false;
				}
			}
			else {
				t = (elapsedTime - 34) / 2;
				robot->body->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, Math::PI / 2.5, 0), Vector3(0, Math::PI / 1, 0), t)));
			}
		}
		else if (elapsedTime > 36.0 && elapsedTime < 39.0) {
			if (!isWalking) {
				walkingAnime->play();
				isWalking = true;
			}
			t = (elapsedTime - 36) / 3;
			robot->getTransform()->setLocalPosition(Vector3::lerp(Vector3(.8, 0, 1), Vector3(.8, 0, -0.7), t));
		}
		else if (elapsedTime > 39.0 && elapsedTime < 40.0) {
			if (isWalking) {
				walkingAnime->pause();
				isWalking = false;
			}
		}
		else if (elapsedTime > 40.0 && elapsedTime < 41.0) {
			t = (elapsedTime - 40) / 4;
			robot->leftHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(Math::PI, Math::PI / 2, 0), Vector3(Math::PI, Math::TWO_PI, 0), t)));
		}
		else if (elapsedTime > 41.0 && elapsedTime < 42.0) {
			t = (elapsedTime - 41) / 4;
			robot->leftHandJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(Math::PI, Math::TWO_PI, 0), Vector3(Math::PI, -Math::TWO_PI, 0), t)));
		}
		else {
			//do nothing
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