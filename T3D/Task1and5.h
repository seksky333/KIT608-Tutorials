#pragma once
#include "WinGLApplication.h"
#include "Robot.h"
#include "Animation.h"
namespace T3D {

	class Task1and5 :public WinGLApplication
	{
	public:
		bool init();
		void addRobotWalking(std::string element, int startFramePos, int endFramePos, Animation* anim);

	};
}

