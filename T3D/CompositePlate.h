#include "Mesh.h"
#include "GameObject.h"
#include "SweepPath.h"
#include "Plate.h"
namespace T3D
{
	class CompositePlate :public GameObject
	{
	public:
		//! \brief Create Cube with volume = `size^3`.
		CompositePlate(T3DApplication* app);
		~CompositePlate(void);

		std::vector<Vector3> getLegProfile();

		GameObject* plate;
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
		Transform t;
	};

}