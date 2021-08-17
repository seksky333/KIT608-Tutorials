
#pragma once
#include "Mesh.h"
namespace T3D
{
	class Cylinder :public Mesh
	{
	public:
		//! \brief Create Cube with volume = `size^3`.
		Cylinder(int r, int h, int d);

		//! \brief Destroy Cube.
		/*! \note Mesh superclass deletes arrays if they have been created, no need to do anything here
		*/
		virtual ~Cylinder(void) = default;

	};

}