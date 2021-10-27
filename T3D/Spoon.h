#include "Mesh.h"
#include "GameObject.h"
#include "SweepPath.h"
namespace T3D
{
	class Spoon :public GameObject
	{
	public:
		//! \brief Create Cube with volume = `size^3`.
		Spoon(T3DApplication* app);
		~Spoon(void);

		std::vector<Vector3> getLegProfile();

		GameObject* spoonBody;
		GameObject* spoonHead;
		GameObject* headJoint;

		GameObject* leftLegJoint;
		GameObject* leftLeg;
		GameObject* leftFootJoint;
		GameObject* leftFoot;

		GameObject* rightLegJoint;
		GameObject* rightLeg;
		GameObject* rightFootJoint;
		GameObject* rightFoot;

		SweepPath leftLegSP;
		SweepPath rightLegSP;
		SweepPath spoonBodySP;
		Transform t;
	};

}