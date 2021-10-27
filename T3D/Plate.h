
#pragma once
#include "Mesh.h"
namespace T3D
{
	class Plate :public Mesh
	{
	public:
		//! \brief Create Cube with volume = `size^3`.
		Plate(float r, float h, int d);

		//! \brief Destroy Cube.
		/*! \note Mesh superclass deletes arrays if they have been created, no need to do anything here
		*/
		virtual ~Plate(void) = default;

	};

}