#include "Task.h"
#include "GameObject.h"
#include "Animation.h"

namespace T3D {

	class CameraTask :public Task
	{
	public:
		bool init();
		CameraTask(T3DApplication* app);
		void update(float dt);

		GameObject* camObj;
		float elapsedTime;
	};

}

