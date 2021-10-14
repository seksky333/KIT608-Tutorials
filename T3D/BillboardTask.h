#include "Task.h"
#include "GameObject.h"
namespace T3D {

	class BillboardTask :public Task
	{
	public:
		bool init();
		BillboardTask(T3DApplication* app);
		void update(float dt);

		GameObject* gameObj;
		GameObject* gameObj1;
		GameObject* gameObj2;
		float elapsedTime;
	};

}