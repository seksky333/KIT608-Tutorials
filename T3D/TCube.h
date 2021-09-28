#include "Mesh.h"

namespace T3D
{
	//! \brief A simple parametric Cube Mesh.
	class TCube :
		public Mesh
	{
	public:
		void init();
		//! \brief Create Cube with volume = `size^3`.
		TCube(float size);

		//! \brief Destroy Cube.
		/*! \note Mesh superclass deletes arrays if they have been created, no need to do anything here
		*/
		virtual ~TCube(void) = default;
	};
}

