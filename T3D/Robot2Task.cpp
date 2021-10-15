#include "Robot2Task.h"
#include "Robot.h"
#include "Animation.h"
#include "Logger.h"

using namespace T3D;
namespace T3D
{
	const float legJPosX = 0.0;
	const float legJPosY = -0.1425;
	const float legJPosZ = 0.10;

	Robot2Task::Robot2Task(T3DApplication* app) : Task(app) {
		elapsedTime = 0;
		robot = NULL;
	}

	void Robot2Task::update(float dt) {
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
		walkingAnime->loop(false);

		//std::string  debugText = "elapsedTime:" + std::to_string(elapsedTime);
		//printf("* Debug: %s \n", debugText.c_str());

		if (elapsedTime < 5.0) {
		}
		else if (elapsedTime > 15.0  && elapsedTime < 17.0) {
			//turn to the front
			if (!isWalking) {
				walkingAnime->play();
				isWalking = true;
			}
			t = (elapsedTime - 15) / 2;
			robot->body->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, Math::PI / 4, 0), Vector3(0, Math::PI / 1.8, 0), t)));
		}

		else if (elapsedTime > 17.0 && elapsedTime < 19.0) {
			//turn walking forward
				if (!isWalking) {
					walkingAnime->play();
					isWalking = true;
				}

				t = (elapsedTime - 17) / 2;
				robot->getTransform()->setLocalPosition(Vector3::lerp(Vector3(0, 0, -1), Vector3(.8, 0, -1), t));
		}
		else if (elapsedTime > 19.0 && elapsedTime < 21.0) {
			//turn right wiht right shoulder up
			if (!isWalking) {
				walkingAnime->play();
				isWalking = true;
			}
			t = (elapsedTime - 19) / 2;
			robot->body->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, Math::PI / 1.8, 0), Vector3(0, Math::PI/6, 0), t)));
			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, 0), Vector3(0, 0, Math::PI / 2), t)));
		}
		else if (elapsedTime > 21.0 && elapsedTime < 23.0) {
			//turn to the front
			//if (elapsedTime > 22.90) {
			//	if (isWalking) {
			//		walkingAnime->pause();
			//		isWalking = false;
			//	}
			//}
			//else {
			t = (elapsedTime - 21) / 2;
			robot->body->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, Math::PI / 6, 0), Vector3(0, Math::PI / 1.8, 0), t)));
			//}
		}
		else if (elapsedTime > 23.0 && elapsedTime < 25.0) {
			if (isWalking) {
				walkingAnime->pause();
				isWalking = false;
			}
			t = (elapsedTime - 23) / 2;
			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 2), Vector3(0, 0, 0), t)));
		}
		else if (elapsedTime > 36.0 && elapsedTime < 38.0) {
			t = (elapsedTime - 36) / 2;
			robot->body->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, Math::PI / 1.8, 0), Vector3(0, -(Math::PI/100) * 1 , 0), t)));
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
			robot->rightArm->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, 0), Vector3(10, 10, -10), t)));

			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, (Math::PI / 100) * 3), Vector3(0, 0, Math::PI / 1.5), t)));
			robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 1.5), Vector3(0, 0, (Math::PI / 100) * 3), t)));
		}
		else if (elapsedTime > 45.0 && elapsedTime < 46.0) {
			t = (elapsedTime - 45) / 1;
			robot->rightArm->setVisible(false);
			robot->rightShoulder->setVisible(false);
			robot->rightHand->setVisible(false);

			robot->leftArm->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, 0), Vector3(10, 10, -10), t)));

			robot->leftShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, Math::PI / 1.5), Vector3(0, 0, (Math::PI / 100) * 3), t)));
			robot->rightShoulderJoint->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, (Math::PI / 100) * 3), Vector3(0, 0, Math::PI / 1.5), t)));
		}
		else if (elapsedTime > 46.0 && elapsedTime < 47.0) {
			t = (elapsedTime - 46) / 1;
			robot->leftArm->setVisible(false);
			robot->leftShoulder->setVisible(false);
			robot->leftHand->setVisible(false);

			robot->rightLeg->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, 0), Vector3(10, 10, -10), t)));
		}
		else if (elapsedTime > 47.0 && elapsedTime < 48.0) {
			t = (elapsedTime - 47) / 1;
			robot->rightLeg->setVisible(false);
			robot->rightFoot->setVisible(false);

			robot->leftLeg->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, 0), Vector3(10, 10, -10), t)));

		}
		else if (elapsedTime > 48.0 && elapsedTime < 49.0) {
			t = (elapsedTime - 48) / 1;
			robot->leftLeg->setVisible(false);
			robot->leftFoot->setVisible(false);

			robot->body->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, 0), Vector3(10, 10, -10), t)));

		}
		else if (elapsedTime > 49.0 && elapsedTime < 50.0) {
			t = (elapsedTime - 49) / 1;
			robot->body->setVisible(false);
			robot->head->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, 0), Vector3(10, 10, -10), t)));
		}
		else if (elapsedTime > 50.0 && elapsedTime < 51.0) {
			t = (elapsedTime - 50) / 1;
			robot->head->setVisible(false);
			robot->leftEye->setVisible(false);
			robot->rightEye->setVisible(false);
		}
		else {
			if (!isWalking) {
				walkingAnime->pause();
				isWalking = false;
			}
			//do nothing
		}
	}

	void Robot2Task::addRobotWalking(std::string element, int startFramePos, int endFramePos, Animation* anim) {
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