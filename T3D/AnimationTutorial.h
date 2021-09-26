#pragma once
#include "WinGLApplication.h"
#include "Lamp.h"

namespace T3D {

	class AnimationTutorial :public WinGLApplication
	{
	public:
		bool init();

		Lamp* lamp;
	};
}

