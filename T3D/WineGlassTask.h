#include "Task.h"
#include "GameObject.h"
#include "WineGlass.h"
#include "Animation.h"

namespace T3D {

	class WineGlassTask :public Task
	{
	public:
		bool init();
		WineGlassTask(T3DApplication* app);
		void update(float dt);

		GameObject* gameObj;
		GameObject* base;
		GameObject* leg1;
		GameObject* leg2;
		GameObject* leg3;
		GameObject* leg4;
		float elapsedTime;
	};

}