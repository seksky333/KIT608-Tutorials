// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// DrawTask.cpp
//
// Simple task for drawing to and animating textures, used in tutorial 1 for practice implementing drawing routines

#pragma once
#include <vector>

#include "Task.h"
#include "T3DApplication.h"
#include "Renderer.h"
#include "Texture.h"
#include "Vector3.h"
#include "Matrix3x3.h"
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>

#include <sstream>

namespace T3D 
{
	//! \brief Task subclass, used for implementing 2D drawing routines. 
	class DrawTask :
		public Task
	{
	public:
		//! \brief Creates a DrawTask that draws onto a Texture every frame.
		DrawTask(T3DApplication *app, Texture* tex);

		//! \brief Destroy DrawTask (trivially). 
		~DrawTask(void) = default;

		//! \brief Ensures that the drawing area is ready to be drawn onto.
		void init();

		//! \brief Draw a coloured line between two points using the Digital Differential Algorithm (DDA) algorithm.
		void drawDDALine(int x1, int y1, int x2, int y2, Colour c);
		void drawDDAFillLine(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2, Colour c);

		//! \brief Draw a coloured line from between two points using the integer-only Bresenham algorithm
		void drawBresLine(int x1, int y1, int x2, int y2, Colour c);

		//! \brief Draw a circle with trigonometry
		void drawCircle(int cx, int cy, int r, Colour c);

		void drawMirrorCircle(int cx, int cy, int r, Colour c);
		void drawMirrorOctantsCircle(int cx, int cy, int r, Colour c);
		void drawCircleWithPythagoras(int cx, int cy, int r, Colour c);

		void drawPieWedge(int cx, int cy, int r, Colour c);

		void tutorialOneDrawing();
		void tutorialTwoDrawing();
		void praticeLabTest();
		void drawLabTest();
		void drawSpoon();
		void drawSpoonTop();
		void testCircles();
		void testFilledShape();
		void drawTriangles(std::vector<Vector3> points);
		void drawPencil(int x1, int y1, int x2, int y2, int r, int d);

		//! \brief Ticks the drawing routine for this frame.
		virtual void update(float dt);

	private:
		Texture *drawArea;
		SDL_Surface* image;			//! \brief Handle to SDL surface
		//! \brief Add a pixel to be displayed this frame to the PixelPlotQueue.
		void pushPixel(int x, int y, Colour colour);

		//! \brief Write all pushed pixel changes to drawArea, displaying errors to the console and log file.
		void flushPixelQueue();

		//! \brief Wrapper for pixel data, used by the pixel plot queue
		struct Pixel
		{
			int x = 0;
			int y = 0;
			Colour colour = { 0xFF, 0, 0xFF, 0xFF }; // Anything dodgy should show up as magenta
		};

		//! \brief One frames worth of pixels to blit onto the drawArea
		std::vector<Pixel> pixelPlotQueue;
		//Vector3 points[4];
		int counter = 0;
		std::vector<Vector3> vectorPoints;
		std::vector<Vector3> points;
		std::vector<Vector3> bodyVector;
		std::vector<Vector3> spoonPoints;
		std::vector<Vector3> spoonTopPoints;
		Matrix3x3 M, R, T1, T2, P, P1, T3, T4, T5, T6, S;
		
	};

}

