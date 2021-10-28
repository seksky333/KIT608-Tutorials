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
		std::vector<Vector3> getHandProfile();
		std::vector<Vector3> getArmProfile();

		GameObject* plate;
		GameObject* spoonHead;
		GameObject* headJoint;
		GameObject* leftShoulder;
		GameObject* leftArm;
		GameObject* leftHand;
		GameObject* rightShoulder;
		GameObject* rightArm;
		GameObject* rightHand;

		GameObject* leftEyeJoint;
		GameObject* leftEye;
		GameObject* rightEyeJoint;
		GameObject* rightEye;

		GameObject* leftShoulderJoint;
		GameObject* leftArmJoint;
		GameObject* leftHandJoint;

		GameObject* leftLegJoint;
		GameObject* leftLeg;
		GameObject* leftFootJoint;
		GameObject* leftFoot;

		GameObject* rightShoulderJoint;
		GameObject* rightArmJoint;
		GameObject* rightHandJoint;

		GameObject* rightLegJoint;
		GameObject* rightLeg;
		GameObject* rightFootJoint;
		GameObject* rightFoot;

		SweepPath leftArmSP;
		SweepPath leftHandSP;
		SweepPath rightArmSP;
		SweepPath rightHandSP;
		SweepPath leftLegSP;
		SweepPath rightLegSP;
		Transform t;
	};

}