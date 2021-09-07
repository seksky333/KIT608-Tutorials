#pragma once
#include "Mesh.h"
namespace T3D
{
	class Tablet :public Mesh
	{
	public:
		//! \brief Create Cube with volume = `size^3`.
		Tablet(Vector3 size, float bezel_width, float corner_radius, float screen_depression, int density);

		//! \brief Destroy Cube.
		/*! \note Mesh superclass deletes arrays if they have been created, no need to do anything here
		*/
		virtual ~Tablet(void) = default;

	};

}