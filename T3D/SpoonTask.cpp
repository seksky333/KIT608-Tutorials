#include "SpoonTask.h"

#include "Animation.h"

using namespace T3D;
namespace T3D
{
	SpoonTask::SpoonTask(T3DApplication* app) : Task(app) {
		elapsedTime = 0;
		spoon = NULL;
	}

	void SpoonTask::update(float dt) {
		float t = 0;
		elapsedTime += dt;
		//t = elapsedTime / 5.0;

		Animation* walkingAnime = new Animation(60.0);
		spoon->addComponent(walkingAnime);


		walkingAnime->addKey("RightLegJoint", 0, Quaternion(Vector3(0, 0, 0)), Vector3(0.0, -.45, -.070));
		addWalking("RightLegJoint", 1, 9, walkingAnime);

		walkingAnime->addKey("LeftLegJoint", 0, Quaternion(Vector3(0, 0, 0)), Vector3(0, -.45, 0.070));
		addWalking("LeftLegJoint", 1, 9, walkingAnime);


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

			spoon->spoonBody->getTransform()->setLocalRotation(Quaternion(Vector3::lerp(Vector3(0, 0, 0), Vector3(0, Math::PI , 0), t)));
		}
		else if (elapsedTime > 4.0 && elapsedTime < 10.0) {
			//run away
			t = (elapsedTime - 4) / 6;
			spoon->getTransform()->setLocalPosition(Vector3::lerp(Vector3(0, 0, -1), Vector3(-8, 0, -1), t));

		}
		else {
			//do nothing
		}
	}

	void SpoonTask::addWalking(std::string element, int startFramePos, int endFramePos, Animation* anim) {
		float framePos = 0.0;
		for (int i = 1; i < 9; i++) {
			framePos = i;
			//if leftLeg
			if (element == "LeftLegJoint") {
				if (i % 2 == 0) {
					anim->addKey(element, framePos, Quaternion(Vector3(0, -Math::PI / 4, 0)), Vector3(0, -.45, 0.070));
				}
				else {
					anim->addKey(element, framePos, Quaternion(Vector3(0,   Math::PI /4, 0)), Vector3(0, -.45, 0.070));
				}
			}
			//if righttLeg
			else {
				if (i % 2 == 0) {
					anim->addKey(element, framePos, Quaternion(Vector3(0, Math::PI / 4, 0)), Vector3(0.0, -.45, -.070));
				}
				else {
					anim->addKey(element, framePos, Quaternion(Vector3(0, -Math::PI/4, 0)), Vector3(0.0, -.45, -.070));
				}
			}

		}
	}
}