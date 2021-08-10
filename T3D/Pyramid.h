#pragma once
#include "Mesh.h"
namespace T3D
{
	class Pyramid:public Mesh
	{
	public:
		//! \brief Create Cube with volume = `size^3`.
		Pyramid(float size);

		//! \brief Destroy Cube.
		/*! \note Mesh superclass deletes arrays if they have been created, no need to do anything here
		*/
		virtual ~Pyramid(void) = default;

	};

}