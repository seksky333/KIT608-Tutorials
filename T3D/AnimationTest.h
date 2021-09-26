#include "Task.h"
#include "Lamp.h"
namespace T3D {

	class AnimationTest :public Task
	{
	public:
		bool init();
		AnimationTest(T3DApplication* app);
		void update(float dt);

		T3D::Transform* lampTransform;
		float elapsedTime;
	};
}

