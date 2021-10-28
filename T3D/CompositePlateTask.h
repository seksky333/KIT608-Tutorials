

#include "Task.h"
#include "CompositePlate.h"
#include "Animation.h"
namespace T3D {

	class CompositePlateTask :public Task
	{
	public:
		bool init();
		bool isWalking = false;
		CompositePlateTask(T3DApplication* app);
		void update(float dt);
		void addWalking(std::string element, int startFramePos, int endFramePos, Animation* anim);

		CompositePlate* compositePlate;
		float elapsedTime;
	};

}