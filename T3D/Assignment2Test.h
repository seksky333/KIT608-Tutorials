#pragma once
#include "WinGLApplication.h"
#include "Robot.h"
#include "Animation.h"
namespace T3D {

	class Assignment2Test :public WinGLApplication
	{
	public:
		bool init();
		void addRunningAnime(std::string element, int startFramePos, int endFramePos, Animation* anim);

	};
}

