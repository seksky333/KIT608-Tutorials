#include "Task.h"
#include "Spoon.h"
#include "Animation.h"
namespace T3D {

	class SpoonTask :public Task
	{
	public:
		bool init();
		bool isWalking = false;
		SpoonTask(T3DApplication* app);
		void update(float dt);
		void addWalking(std::string element, int startFramePos, int endFramePos, Animation* anim);

		Spoon* spoon;
		float elapsedTime;
	};

}