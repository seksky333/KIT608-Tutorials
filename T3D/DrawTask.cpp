// =========================================================================================
// KXG363 - Advanced Games Programming
// =========================================================================================
//
// Author: Robert Ollington
//
// GameObject.cpp
//
// Simple task for drawing to and animating textures, used in tutorial 1 for practice implementing drawing routines

#include <math.h>
#include "Renderer.h"
#include "DrawTask.h"
#include "Logger.h"
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>

namespace T3D 
{
	/*
	 * \param app Application root
	 * \param tex Texture to draw onto
	 *
	 * \note `tex` should be initialised, and registered with the renderer as both a loaded Texture and a 2D Overlay. This can be done using `new Texture(...)`, `loadTexture(...)`, and finally `add2DOverlay(...)`.
	 * \note If nothing is drawing on the screen, ensure the returned DrawTask object is added to the list of Tasks from the callsite using `addTask(...).
	 * \note If there is nothing on the screen still, check the visual studio console for error messages in case something is out of bounds.
	 *
	 */
	DrawTask::DrawTask(T3DApplication *app, Texture* tex) : Task(app)
	{
		drawArea = tex;
		

		// @BoundsCheck - requires using pushPixel
		// Reserve some space for the buffer, as its unlikely only few pixels will be plotted
		// const uint32_t pixelsToReserve = 512;
		// pixelPlotQueue.reserve(pixelsToReserve);

		init();
		logger::Log(priority::Info, output_stream::All, category::Task, "Initialised DrawTask");
	}

	/*
	 * \param 
	 * \note This isn't necessary. It could be inlined into the constructor.
	 */
	void DrawTask::init	(){		


		drawArea->clear(Colour(255,255,255,255));
		drawDDALine(100,100,200,200,Colour(0,0,0,255));
	}

	/*
	 * \param x1 Start x pixel coordinate 
	 * \param y1 Start y pixel coordinate
	 * \param x2 End x pixel coordinate 
	 * \param y2 End y pixel coordinate
	 * \param Colour of line
	 *
	 * \note Uses floating-point numbers as seen in the 2D graphics lecture.
	 * \note `pushPixel` is used to do large batches of *bounds-checked* pixel drawing, which you may prefer to your application crashing if you go outside the texture area.
	 */
	void DrawTask::drawDDALine(int x1, int y1, int x2, int y2,Colour c){

		float  step, x, y;

		float deltax = (float(x2 - x1)); 
		float deltay = (float(y2 - y1));
		
		//float dy = deltay / deltax;
		if (abs(deltax) >= abs(deltay))
			step = abs(deltax);
		else
			step = abs(deltay);

		deltax = deltax / step;
		deltay = deltay / step;
		//set starting position for drawing
		x = x1;
		y = y1;
		for (int i = 0; i < step; i++) {
			drawArea->plotPixel(x, y, c);
			x += deltax;
			y += deltay;
		}
	}
	void DrawTask::drawBresLine(int x1, int y1, int x2, int y2, Colour c){
		int  step, x, y, error;
		bool isXGreater;
		// Part of Bresenham’s algo
		int deltay = (y2 - y1);
		int deltax = (x2 - x1);
		
		//float dy = deltay / deltax;
		if (abs(deltax) >= abs(deltay)) {
			step = abs(deltax);
			error = deltax / 2;
		}else{
			step = abs(deltay);
			error = deltay / 2;
		}
			

		deltax = deltax / step;
		deltay = deltay / step;
		//set starting position for drawing
		x = x1;
		y = y1;
		for (int i = 0; i < step; i++) {
			drawArea->plotPixel(x, y, c);
			x += deltax;
			y += deltay;
		}

	}


	void DrawTask::drawCircle(int cx, int cy, int r, Colour c) {
		const double PI = 3.141592653589793238463;
		const double unitCircleCircumference = 2 * PI;
		float  step, x, y ;
		step = 0.001;
		for (float theta = 0; theta < unitCircleCircumference; theta += step) {
			x = cx + r * cos(theta);
			y = cy + r * sin(theta);
			drawArea->plotPixel(x, y, c);
		}
	}

	void DrawTask::drawMirrorCircle(int cx, int cy, int r, Colour c) {
		const double PI = 3.141592653589793238463;
		const double unitCircleCircumference = PI / 2;
		float  step, x, y;
		step = 0.001;
		for (float theta = 0; theta < unitCircleCircumference; theta += step) {
			x = r * cos(theta);
			y = r * sin(theta);
			drawArea->plotPixel(cx + x, cy + y, c);
			drawArea->plotPixel(cx + x, cy - y, c);
			drawArea->plotPixel(cx - x, cy + y, c);
			drawArea->plotPixel(cx - x, cy - y, c);
		}
	}
	void DrawTask::drawMirrorOctantsCircle(int cx, int cy, int r, Colour c) {
		const double PI = 3.141592653589793238463;
		const double unitCircleCircumference = PI / 4;
		float  step, x, y;
		step = 0.001;
		for (float theta = 0; theta <= unitCircleCircumference; theta += step) {
			x = r * cos(theta);
			y = r * sin(theta);
			drawArea->plotPixel(cx + x, cy + y, c); drawArea->plotPixel(cx + y, cy + x, c);
			drawArea->plotPixel(cx + x, cy - y, c); drawArea->plotPixel(cx - y, cy + x, c);
			drawArea->plotPixel(cx - x, cy + y, c); drawArea->plotPixel(cx + y, cy - x, c);
			drawArea->plotPixel(cx - x, cy - y, c); drawArea->plotPixel(cx - y, cy - x, c);
		}
	}
	void DrawTask::drawCircleWithPythagoras(int cx, int cy, int r, Colour c) {
		float  x, y;

		for (y = 0; y <= r / sqrt(2); y++) {
			x = sqrt(r * r - y * y);
			drawArea->plotPixel(cx + x, cy + y, c); drawArea->plotPixel(cx + y, cy + x, c);
			drawArea->plotPixel(cx + x, cy - y, c); drawArea->plotPixel(cx - y, cy + x, c);
			drawArea->plotPixel(cx - x, cy + y, c); drawArea->plotPixel(cx + y, cy - x, c);
			drawArea->plotPixel(cx - x, cy - y, c); drawArea->plotPixel(cx - y, cy - x, c);
		}


	}

	void DrawTask::testCircles() {
		using std::chrono::high_resolution_clock;
		using std::chrono::duration_cast;
		using std::chrono::duration;
		using std::chrono::milliseconds;

		auto t1 = high_resolution_clock::now();

		for (int i= 100; i < 500; i += 1) {
			drawCircle(i, i, 100, Colour(255, 0, 0, 255));
			//drawMirrorCircle(i, i, 100, Colour(255, 0, 0, 255));
			//drawMirrorOctantsCircle(i, i, 100, Colour(255, 0, 0, 255));
			//drawCircleWithPythagoras(i, i, 100, Colour(255, 0, 0, 255));
		}
		auto t2 = high_resolution_clock::now();

		/* Getting number of milliseconds as an integer. */
		auto ms_int = duration_cast<milliseconds>(t2 - t1);

		std::string outputText = "ms_int: " + std::to_string(ms_int.count());

		logger::Log(priority::Info, output_stream::All, category::Task, outputText.c_str());
	}


	/*
	 * \param dt Change in time
	 *
	 * \note Make sure to clear the `drawArea` before you write to it.
	 */
	void DrawTask::update(float dt){
		drawArea->clear(Colour(255, 255, 255, 255));

		//testCircles();
		/*
		drawCircle( 200,200,200,Colour(255, 0, 0, 255));
		drawMirrorCircle( 100,100,100,Colour(255, 0, 0, 255));
		drawMirrorOctantsCircle(300, 300, 300, Colour(255, 0, 0, 255));
		*/
		drawCircleWithPythagoras(100, 100, 100, Colour(255, 0, 0, 255));

		//drawDDALine(100, 100, 200, 100, Colour(255, 0, 0, 255));
		//drawBresLine(100, 100, 100, 0, Colour(255, 0, 0, 255));
		//drawBresLine(100, 100, 100, 200, Colour(60, 179, 113, 255));
		
		
		//red right
		drawBresLine(100, 100, 200, 100, Colour(255, 0, 0, 255));
		//blue left
		drawBresLine(100, 100, 0, 100, Colour(0, 0, 255, 255));
		//green down
		drawBresLine(100, 100, 100, 200, Colour(60, 179, 113, 255));
		//yellow up
		drawBresLine(100, 100, 100, 0, Colour(255, 165, 0, 255));
		
		/*
		**************
		DEBUG AREA
		**************
		//red north east
		drawBresLine(100, 100, 170, 30, Colour(255, 0, 0, 255));
		//blue south east
		drawBresLine(100, 100, 170, 170, Colour(0, 0, 255, 255));
		*/

		
		//red north east
		drawBresLine(100, 100, 170, 30, Colour(255, 0, 0, 255));
		//blue south east
		drawBresLine(100, 100, 170, 170, Colour(0, 0, 255, 255));
		//yellow north west
		drawBresLine(100, 100, 30, 30, Colour(255, 165, 0, 255));
		//green south west
		drawBresLine(100, 100, 30, 170, Colour(60, 179, 113, 255));
		
		/*
		//red  between north and north east
		drawBresLine(100, 100, 140, 10, Colour(128, 0, 0, 255));
		//red  between south and south east
		drawBresLine(100, 100, 140, 190, Colour(128, 0, 0, 255));
		//red  between north and north east
		drawBresLine(100, 100, 55, 10, Colour(128, 0, 0, 255));
		//red  between south and south west
		drawBresLine(100, 100, 55, 190, Colour(128, 0, 0, 255));
		*/

		// @BoundsCheck- requires using pushPixel
		// Plots pixels made to the drawArea this frame, clearing the pixel queue.
		// flushPixelQueue();
		app->getRenderer()->reloadTexture(drawArea);
	}

	/*
	 * Provides a bounds-checked and more efficient way to draw onto a surface then `plotPixel()`.
	 * Diagnostic messages for out-of-bounds drawing are displayed onto the console, and into `T3D_Log.txt`.
	 * 
	 * \param x x pixel coordinate to draw onto
	 * \param y y pixel coordinate to draw onto
	 * \param Colour pixel colour
	 *
	 */
	void DrawTask::pushPixel(int x, int y, Colour colour)
	{
		pixelPlotQueue.push_back(Pixel { x, y, colour }); 
	}

	/*
	 * Provides a bounds-checked and more efficient way to draw onto a surface then `plotPixel()`.
	 * Diagnostic messages for out-of-bounds drawing are displayed onto the console, and into `T3D_Log.txt`.
	 *
	 *
	 * \note This should be called at the end of the `update` function.
	 */
	void DrawTask::flushPixelQueue()
	{
		const uint32_t MaxOutOfBoundsCount = 10u;
		uint32_t OutOfBoundsCount = 0u;
		for (auto &Pixel : pixelPlotQueue)
		{
			bool PixelWithinWidth  = (Pixel.x >= 0 && Pixel.x < drawArea->getWidth());
			bool PixelWithinHeight = (Pixel.y >= 0 && Pixel.y < drawArea->getHeight());
			bool PixelWithinBounds = (PixelWithinWidth && PixelWithinHeight);

			if (PixelWithinBounds)
			{
				drawArea->plotPixel(Pixel.x, Pixel.y, Pixel.colour);
			}
			else 
			{
				if (OutOfBoundsCount < MaxOutOfBoundsCount)
				{
					logger::Log(priority::Tracing,
							    output_stream::File,
							    category::Debug,
							   "Pixel out of bounds!\n"
							   "\tWidth  :: [0 <= X <= %4u :: %4d :: %5s]%s\n"
							   "\tHeight :: [0 <= Y <= %4u :: %4d :: %5s]%s\n"
							   ,
							   app->getRenderer()->WindowWidth,
							   Pixel.x, PixelWithinWidth  ? "OK" : "ERROR",
							   PixelWithinWidth  ?   ""  : " <<<\n",
							   app->getRenderer()->WindowHeight,
							   Pixel.y, PixelWithinHeight ? "OK" : "ERROR",
							   PixelWithinHeight  ?  ""  : " <<<\n");
				}
				OutOfBoundsCount++;
			}
		}

		if (OutOfBoundsCount >= MaxOutOfBoundsCount)
		{
			logger::Log(priority::Tracing,
						output_stream::File,
						category::Debug,
					   "... Repeats %u times ...\n"
					   ,
					   OutOfBoundsCount - MaxOutOfBoundsCount);
		}

		pixelPlotQueue.clear();
	}



}
