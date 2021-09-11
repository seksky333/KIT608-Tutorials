#pragma once
#include "GameObject.h"
#include "SweepPath.h"
namespace T3D
{

	class Rectangle : public Mesh
	{
	public:
		Rectangle(Vector3 size);
		virtual ~Rectangle(void) = default;
	};


}