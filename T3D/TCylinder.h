#include "Mesh.h"

namespace T3D
{
	//! \brief A simple parametric Cube Mesh.
	class TCylinder :
		public Mesh
	{
	public:
		void init();
		//! \brief Create Cube with volume = `size^3`.
		TCylinder(float r, float h, int d);

		//! \brief Destroy Cube.
		/*! \note Mesh superclass deletes arrays if they have been created, no need to do anything here
		*/
		virtual ~TCylinder(void) = default;
	};
}

