#include "Task.h"
#include "Robot.h"
#include "Animation.h"
namespace T3D {

	class Robot1Task :public Task
	{
	public:
		bool init();
		bool isWalking = false;
		Robot1Task(T3DApplication* app);
		void update(float dt);
		void addRobotWalking(std::string element, int startFramePos, int endFramePos, Animation* anim);

		Robot* robot;
		float elapsedTime;
	};

}