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
		else if (elapsedTime > 10.0 && elapsedTime < 11.0) {
			//testing
			t = (elapsedTime - 10) / 1;
			

		}
		else if (elapsedTime > 11.0 && elapsedTime < 12.0) {
			t = (elapsedTime - 11) / 1;

		}
		else if (elapsedTime > 12.0 && elapsedTime < 13.0) {
			t = (elapsedTime - 12) / 1;

		}
		else if (elapsedTime > 13.0 && elapsedTime < 14.0) {
			t = (elapsedTime - 13) / 1;

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
			//if (!isWalking) {
			//	walkingAnime->play();
			//	isWalking = true;
			//}
			t = (elapsedTime - 36) / 3;
			robot->getTransform()->setLocalPosition(Vector3::lerp(Vector3(.8, 0, 1), Vector3(.8, 0, -0.5), t));
		}
		else if (elapsedTime > 39.0 && elapsedTime < 40.0) {
			if (isWalking) {
				walkingAnime->pause();
				isWalking = false;
			}
		}
		else if (elapsedTime > 40.0 && elapsedTime < 41.0) {
			t = (elapsedTime - 40) / 1;
			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, 0), Vector3(0, 0, Math::PI / 1.5), t)));
			robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, 0), Vector3(0, 0, (Math::PI / 100) * 3), t)));
		}
		else if (elapsedTime > 41.0 && elapsedTime < 42.0) {
			t = (elapsedTime - 41) / 1;
			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 1.5), Vector3(0, 0, (Math::PI / 100) * 3), t)));
			robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, (Math::PI / 100) * 3), Vector3(0, 0, Math::PI / 1.5), t)));

		}
		else if (elapsedTime > 42.0 && elapsedTime < 43.0) {
			t = (elapsedTime - 42) / 1;
			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, (Math::PI / 100) * 3), Vector3(0, 0, Math::PI / 1.5), t)));
			robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 1.5), Vector3(0, 0, (Math::PI / 100) * 3), t)));
		}
		else if (elapsedTime > 43.0 && elapsedTime < 44.0) {
			t = (elapsedTime - 43) / 1;
			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 1.5), Vector3(0, 0, (Math::PI / 100) * 3), t)));
			robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, (Math::PI / 100) * 3), Vector3(0, 0, Math::PI / 1.5), t)));
		}

		else if (elapsedTime > 44.0 && elapsedTime < 45.0) {
			t = (elapsedTime - 44) / 1;
			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, (Math::PI / 100) * 3), Vector3(0, 0, Math::PI / 1.5), t)));
			robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 1.5), Vector3(0, 0, (Math::PI / 100) * 3), t)));
		}
		else if (elapsedTime > 45.0 && elapsedTime < 46.0) {
			t = (elapsedTime - 45) / 1;
			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 1.5), Vector3(0, 0, (Math::PI / 100) * 3), t)));
			robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, (Math::PI / 100) * 3), Vector3(0, 0, Math::PI / 1.5), t)));
		}
		else if (elapsedTime > 46.0 && elapsedTime < 47.0) {
			t = (elapsedTime - 46) / 1;
			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, (Math::PI / 100) * 3), Vector3(0, 0, Math::PI / 1.5), t)));
			robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 1.5), Vector3(0, 0, (Math::PI / 100) * 3), t)));
		}
		else if (elapsedTime > 47.0 && elapsedTime < 48.0) {
			t = (elapsedTime - 47) / 1;
			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 1.5), Vector3(0, 0, (Math::PI / 100) * 3), t)));
			robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, (Math::PI / 100) * 3), Vector3(0, 0, Math::PI / 1.5), t)));
		}
		else if (elapsedTime > 48.0 && elapsedTime < 49.0) {
			t = (elapsedTime - 48) / 1;
			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, (Math::PI / 100) * 3), Vector3(0, 0, Math::PI / 1.5), t)));
			robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 1.5), Vector3(0, 0, (Math::PI / 100) * 3), t)));
		}
		else if (elapsedTime > 49.0 && elapsedTime < 50.0) {
			t = (elapsedTime - 49) / 1;
			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 1.5), Vector3(0, 0, (Math::PI / 100) * 3), t)));
			robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, (Math::PI / 100) * 3), Vector3(0, 0, Math::PI / 1.5), t)));
		}
		else if (elapsedTime > 51.0 && elapsedTime < 52.0) {
		t = (elapsedTime - 51) / 1;
		robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, (Math::PI / 100) * 3), Vector3(0, 0, 0), t)));
		robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 1.5), Vector3(0, 0, 0), t)));
		}
		else if (elapsedTime > 52.0 && elapsedTime < 53.0) {
		t = (elapsedTime - 52) / 1;
		robot->body->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, Math::PI / 1, 0), Vector3(0, Math::PI / 2.0, 0), t)));
		/*robot->body->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, Math::PI / 1, 0), Vector3(0, Math::PI / 2.5, 0), t)));*/
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