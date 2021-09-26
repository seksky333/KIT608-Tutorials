#include "Component.h"
#include "Lamp.h"
#include "Transform.h"
namespace T3D
{

	class LampBehaviour : public Component
	{
	public:
		LampBehaviour() { };
		~LampBehaviour(void) = default;
		void update(float dt);


		T3D::Transform* lampTransform;
		float elapsedTime;
	};

}