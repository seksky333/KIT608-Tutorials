#include "CompositePlateTask.h"
#include "Animation.h"

using namespace T3D;
namespace T3D
{
	CompositePlateTask::CompositePlateTask(T3DApplication* app) : Task(app) {
		elapsedTime = 0;
		compositePlate = NULL;
	}

	void CompositePlateTask::update(float dt) {
		float t = 0;
		elapsedTime += dt;
		//t = elapsedTime / 5.0;

		Animation* walkingAnime = new Animation(60.0);
		compositePlate->addComponent(walkingAnime);

		//walkingAnime->addKey("RightLegJoint", 0, Quaternion(Vector3(-legJPosX, -legJPosY, legJPosZ)), Vector3(-legJPosX, -legJPosY, legJPosZ));

		walkingAnime->addKey("RightLegJoint", 0.0, Quaternion(Vector3(-Math::PI / 2, 0, 0)), Vector3(-0.20, -0.011, 0.4));
		addWalking("RightLegJoint", 1, 9, walkingAnime);

		walkingAnime->addKey("LeftLegJoint", 0, Quaternion(Vector3(-Math::PI / 2, 0, 0)), Vector3(0.20, -0.011, 0.4));
		addWalking("LeftLegJoint", 1, 9, walkingAnime);
		// 
		//walkingAnime->addKey("LeftLegJoint", 10.0, Quaternion(Vector3(legJPosX, -legJPosY, legJPosZ)), Vector3(legJPosX, -legJPosY, legJPosZ));


		//< 5
		if (elapsedTime < 3.0) {
			//do nothing
		}
		else if (elapsedTime > 3.0 && elapsedTime < 4.0) {
			//turn  around
			if (!isWalking) {
				walkingAnime->play();
				isWalking = true;
			}
			t = (elapsedTime - 3) / 1;

			compositePlate->plate->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(Math::PI / 2, Math::PI / 2, 0), Vector3(Math::PI / 2, -Math::PI/2 , 0), t)));
		}
		else if (elapsedTime > 4.0 && elapsedTime < 10.0) {
			//run away
			t = (elapsedTime - 4) / 6;
			compositePlate->getTransform()->setLocalPosition(Vector3::lerp(Vector3(0, 0, 1), Vector3(-8, 0, 1), t));

		}
		else {
			//do nothing
		}
	}

	void CompositePlateTask::addWalking(std::string element, int startFramePos, int endFramePos, Animation* anim) {
		float framePos = 0.0;
		for (int i = 1; i < 9; i++) {
			framePos = i;
			//if leftLeg
			if (element == "LeftLegJoint") {
				if (i % 2 == 0) {
					anim->addKey(element, framePos, Quaternion(Vector3(-Math::PI/4 , 0, 0)), Vector3(0.20, -0.011, 0.4));
				}
				else {
					anim->addKey(element, framePos, Quaternion(Vector3( Math::PI , 0, 0)), Vector3(0.20, -0.011, 0.4));
				}
			}
			//if righttLeg
			else {
				if (i % 2 == 0) {
					anim->addKey(element, framePos, Quaternion(Vector3(Math::PI, 0, 0)), Vector3(-0.20, -0.011, 0.4));
				}
				else {
					anim->addKey(element, framePos, Quaternion(Vector3(-Math::PI / 4, 0, 0)), Vector3(-0.20, -0.011, 0.4));
				}
			}

		}
	}
}