#include "Exam2d.h"
#include "WinGLApplication.h"
#include "GLRenderer.h"
#include "Camera.h"

namespace T3D
{
	Exam2d::Exam2d(void)
	{
		drawTask = nullptr;
		drawArea = new Texture(renderer->WindowWidth, renderer->WindowHeight, false);
		drawArea->clear(Colour(255, 255, 255, 255));
	}

	bool Exam2d::init() {
		WinGLApplication::init();

		renderer->loadTexture(drawArea, false);
		renderer->add2DOverlay(drawArea, 0, 0);

		drawTask = new DrawTask(this, drawArea);
		addTask(drawTask);

		return true;
	}

}