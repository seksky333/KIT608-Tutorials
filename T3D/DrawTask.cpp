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
#include "Math.h"
#include "Texture.h"
#include "Renderer.h"
#include "DrawTask.h"
#include "Logger.h"
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include<windows.h>


namespace T3D
{
	enum class ANIMATION_STATE { DEFAULT, FORWARD, BACKWARD, STOP };

	const int xStartPos = 512;
	const int yStartPos = 320;



	ANIMATION_STATE animeState = ANIMATION_STATE::DEFAULT;
	/*
	 * \param app Application root
	 * \param tex Texture to draw onto
	 *
	 * \note `tex` should be initialised, and registered with the renderer as both a loaded Texture and a 2D Overlay. This can be done using `new Texture(...)`, `loadTexture(...)`, and finally `add2DOverlay(...)`.
	 * \note If nothing is drawing on the screen, ensure the returned DrawTask object is added to the list of Tasks from the callsite using `addTask(...).
	 * \note If there is nothing on the screen still, check the visual studio console for error messages in case something is out of bounds.
	 *
	 */
	DrawTask::DrawTask(T3DApplication* app, Texture* tex) : Task(app)
	{
		Uint32 rmask, gmask, bmask, amask;

		/* SDL interprets each pixel as a 32-bit number, so our masks must depend
		   on the endianness (byte order) of the machine */
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			rmask = 0xff000000;
			gmask = 0x00ff0000;
			bmask = 0x0000ff00;
			amask = 0x000000ff;
		}
		else {
			rmask = 0x000000ff;
			gmask = 0x0000ff00;
			bmask = 0x00ff0000;
			amask = 0xff000000;
		}

		drawArea = tex;
		image = SDL_CreateRGBSurface(0, 1024, 640, 32, rmask, gmask, bmask, amask);

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
	void DrawTask::init() {
		ANIMATION_STATE animeState = ANIMATION_STATE::DEFAULT;
		drawArea->clear(Colour(255, 255, 255, 255));
		//points[0] = Vector3(xStartPos - 50, yStartPos, 1);
		//points[1] = Vector3(xStartPos - 50, yStartPos + 100, 1);
		//points[2] = Vector3(xStartPos + 50, yStartPos + 100, 1);
		//points[3] = Vector3(xStartPos + 50, yStartPos, 1);

		//points[0] = Vector3(xStartPos - 50, yStartPos -50, 1);
		//points[1] = Vector3(xStartPos - 50, yStartPos + 50, 1);
		//points[2] = Vector3(xStartPos + 50, yStartPos + 50, 1);
		//points[3] = Vector3(xStartPos + 50, yStartPos - 50, 1);

		//vectorPoints.push_back(points[0]);
		//vectorPoints.push_back(points[1]);
		//vectorPoints.push_back(points[2]);
		//vectorPoints.push_back(points[3]);



		const float rDegree = 1;
		//rotation
		R = Matrix3x3(cos(rDegree * Math::DEG2RAD), -sin(rDegree * Math::DEG2RAD), 0,
			sin(rDegree * Math::DEG2RAD), cos(rDegree * Math::DEG2RAD), 0,
			0, 0, 1);

		//scale
		S = Matrix3x3(1.01, 0, 0,
			0, 1.01, 0,
			0, 0, 1);


		T1 = Matrix3x3(1, 0, -50,
			0, 1, -50,
			0, 0, 1);

		T2 = Matrix3x3(1, 0, 50,
			0, 1, 50,
			0, 0, 1);


		T3 = Matrix3x3(1, 0, -xStartPos,
			0, 1, -yStartPos,
			0, 0, 1);

		T4 = Matrix3x3(1, 0, xStartPos,
			0, 1, yStartPos,
			0, 0, 1);

		P = T2 * R * T1;
		P1 = T4 * R * T3;
	}

	/*
 * \param dt Change in time
 *
 * \note Make sure to clear the `drawArea` before you write to it.
 */
	void DrawTask::update(float dt) {
		//if (counter > 1000) {
		//	animeState = ANIMATION_STATE::STOP;
		//}
		//else {
		//	counter++;
		//	printf("Counter: %d\n", counter);
		//}

		//const int xStartPosition = 250;
		//const int yStartPosition = 250;

		drawArea->clear(Colour(255, 255, 255, 255));
		//tutorialOneDrawing();
		//tutorialTwoDrawing();
		//praticeLabTest();
		//testCircles();
		drawPieWedge(xStartPos + 0, yStartPos, 100, Colour(255, 0, 0, 255));
		//drawPencil(xStartPos, yStartPos, xStartPos +50, yStartPos - 50, 100, 35);
		// 
		//std::vector<Vector3> points;
		//points.push_back(Vector3(xStartPos + 0, yStartPos + 0, 1));
		//points.push_back(Vector3(xStartPos + 50, yStartPos + 0, 1));
		//points.push_back(Vector3(xStartPos + 100, yStartPos - 100, 1));

		//if (points.empty()) {
		//	points.push_back(Vector3(xStartPosition - 50, yStartPosition - 50, 1));
		//	points.push_back(Vector3(xStartPosition - 50, yStartPosition + 50, 1));
		//	points.push_back(Vector3(xStartPosition + 50, yStartPosition + 50, 1));
		//	points.push_back(Vector3(xStartPosition + 50, yStartPosition - 50, 1));
		//}


		//T5 = Matrix3x3(1, 0, -250,
		//	0, 1, -250,
		//	0, 0, 1);

		//T6 = Matrix3x3(1, 0, 250,
		//	0, 1, 250,
		//	0, 0, 1);

		//M = Matrix3x3(1.01, 0, 0,
		//	0, 0.99, 0,
		//	0, 0, 1);

		//S = T6 * M * T5;

		//for (int i = 0; i < points.size(); i++)
		//{
		//	points[i] = S * points[i];
		//}

		//for (int j = 0; j < points.size(); j++)
		//{
		//	drawDDALine(points[j].x, points[j].y, points[(j + 1) % points.size()].x, points[(j + 1) % points.size()].y, Colour(60, 179, 113, 255));
		//}




		//drawTriangles(points);


		// @BoundsCheck- requires using pushPixel
		// Plots pixels made to the drawArea this frame, clearing the pixel queue.
		flushPixelQueue();
		app->getRenderer()->reloadTexture(drawArea);
	}
	void DrawTask::drawDDAFillLine(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2, Colour c) {
		float  step, step2, x, y, xx, yy;

		float deltax = (float(x2 - x1));
		float deltay = (float(y2 - y1));

		float deltaxx = (float(xx2 - xx1));
		float deltayy = (float(yy2 - yy1));
		//float dy = deltay / deltax;
		if (abs(deltax) >= abs(deltay))
			step = abs(deltax);
		else
			step = abs(deltay);

		if (abs(deltaxx) >= abs(deltayy))
			step2 = abs(deltaxx);
		else
			step2 = abs(deltayy);

		deltax = deltax / step;
		deltay = deltay / step;
		deltaxx = deltaxx / step2;
		deltayy = deltayy / step2;
		//set starting position for drawing
		x = x1;
		y = y1;
		xx = xx1;
		yy = yy1;
		for (int i = 0; i < step; i++) {
			//drawArea->plotPixel(x, y, c);
			pushPixel(x, y, c);
			pushPixel(xx, yy, c);
			drawDDALine(x, y, xx, yy, Colour(255, 165, 0, 255));
			x += deltax;
			y += deltay;

			xx += deltaxx;
			yy += deltayy;
		}
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
	void DrawTask::drawDDALine(int x1, int y1, int x2, int y2, Colour c) {

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
			//drawArea->plotPixel(x, y, c);
			pushPixel(x, y, c);
			x += deltax;
			y += deltay;
		}
	}
	void DrawTask::drawBresLine(int x1, int y1, int x2, int y2, Colour c) {
		int  step, x, y, error;
		bool isXGreater;
		// Part of Bresenham’s algo
		int deltay = (y2 - y1);
		int deltax = (x2 - x1);

		//float dy = deltay / deltax;
		if (abs(deltax) >= abs(deltay)) {
			step = abs(deltax);
			error = deltax / 2;
		}
		else {
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
		float  step, x, y;
		step = 0.001;
		for (float theta = 0; theta < unitCircleCircumference; theta += step) {
			x = cx + r * cos(theta);
			y = cy + r * sin(theta);

			pushPixel(x, y, c);
			drawDDALine(cx, cy, x, y, c);
		}
	}
	void DrawTask::drawMirrorCircle(int cx, int cy, int r, Colour c) {
		const double PI = 3.141592653589793238463;
		const double unitCircleCircumference = PI / 2;
		float  step, x, y;
		step = 0.001;
		//step = 0.1;
		//step = 1;
		for (float theta = 0; theta < unitCircleCircumference; theta += step) {
			x = r * cos(theta);
			y = r * sin(theta);
			drawArea->plotPixel(cx + x, cy + y, c);
			drawArea->plotPixel(cx + x, cy - y, c);
			drawArea->plotPixel(cx - x, cy + y, c);
			drawArea->plotPixel(cx - x, cy - y, c);
			drawDDALine(cx, cy, cx + x, cy + y, c);
			drawDDALine(cx, cy, cx + x, cy - y, c);
			drawDDALine(cx, cy, cx - x, cy + y, c);
			drawDDALine(cx, cy, cx - x, cy - y, c);
			drawDDALine(cx, cy, cx + y, cy + x, c);
			drawDDALine(cx, cy, cx + y, cy - x, c);
			drawDDALine(cx, cy, cx - y, cy + x, c);
			drawDDALine(cx, cy, cx - y, cy - x, c);
			//drawDDALine(cx + x, cy + y, cx - x, cy - y, c);
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
			//border circle
			//upper border circle cy -
			drawArea->plotPixel(cx - y, cy - x, c);
			drawArea->plotPixel(cx + x, cy - y, c);
			drawArea->plotPixel(cx + y, cy - x, c);
			drawArea->plotPixel(cx - x, cy - y, c);

			//lower border circle  cy +
			//left cx - 
			drawArea->plotPixel(cx - x, cy + y, c);
			drawArea->plotPixel(cx - y, cy + x, c);
			//right cx +
			drawArea->plotPixel(cx + y, cy + x, c);
			drawArea->plotPixel(cx + x, cy + y, c);


			//Upper filled circle
			//0 - 45 degree
			drawDDALine(cx, cy, cx - x, cy - y, c);
			//45 - 90 degree
			drawDDALine(cx, cy, cx - y, cy - x, c);
			//90 - 135 degree
			drawDDALine(cx, cy, cx + y, cy - x, c);
			//135 - 180 degree 
			drawDDALine(cx, cy, cx + x, cy - y, c);

			//Lower filled circle
			//0 - 45 degree
			drawDDALine(cx, cy, cx + x, cy + y, c);
			//45 - 90 degree
			drawDDALine(cx, cy, cx + y, cy + x, c);
			//90 - 135 degree
			drawDDALine(cx, cy, cx - y, cy + x, c);
			//135 - 180 degree
			drawDDALine(cx, cy, cx - x, cy + y, c);
		}
	}


	void DrawTask::drawTriangles(std::vector<Vector3> points) {

		for (int j = 0; j < points.size(); j++)
		{
			drawDDALine(points[j].x, points[j].y, points[(j + 1) % points.size()].x, points[(j + 1) % points.size()].y, Colour(60, 179, 113, 255));
		}
	}


	void DrawTask::drawPieWedge(int cx, int cy, int r, Colour c) {
		float  x1, x2;
		int ySquare;
		int y2 = r * sin(180 * Math::DEG2RAD);
		int  rSquare = r * r;

		for (int y = 0; y < y2; y++) {
			ySquare = y * y;
			x1 = y / cos(150 * Math::DEG2RAD);
			//diagonal distance across the shape
			x2 = sqrt(rSquare - ySquare);

			//drawDDALine(cx, cy+ y2, cx + x2, cy + y, c);

			drawDDALine(cx + x2, cy, cx + x2, cy + y, c);

		}
	}

	void DrawTask::testCircles() {
		using std::chrono::high_resolution_clock;
		using std::chrono::duration_cast;
		using std::chrono::duration;
		using std::chrono::milliseconds;

		auto t1 = high_resolution_clock::now();

		for (int i = 0; i < 1; i += 1) {
			//drawCircle(512, 360, 100, Colour(255, 0, 0, 255));
			drawMirrorCircle(512, 360, 100, Colour(255, 0, 0, 255));
			//drawMirrorOctantsCircle(i, i, 100, Colour(255, 0, 0, 255));
			//drawCircleWithPythagoras(512, 360, 100, Colour(255, 0, 0, 255));
		}
		auto t2 = high_resolution_clock::now();

		/* Getting number of milliseconds as an integer. */
		auto ms_int = duration_cast<milliseconds>(t2 - t1);

		std::string outputText = "ms_int: " + std::to_string(ms_int.count());

		logger::Log(priority::Info, output_stream::All, category::Task, outputText.c_str());
	}

	void DrawTask::testFilledShape() {

		drawCircle(512, 320, 100, Colour(255, 0, 0, 255));

		//fillColor(xStartPos, yStartPos, Colour(60, 179, 113, 255));
	}

	void DrawTask::tutorialOneDrawing() {
		drawArea->clear(Colour(255, 255, 255, 255));

		//screen size - 1024 by 640
		//center - 512 by 320

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
		drawDDALine(100, 100, 200, 100, Colour(255, 0, 0, 255));
		//blue left
		drawDDALine(100, 100, 0, 100, Colour(0, 0, 255, 255));
		//green down
		drawDDALine(100, 100, 100, 200, Colour(60, 179, 113, 255));
		//yellow up
		drawDDALine(100, 100, 100, 0, Colour(255, 165, 0, 255));

		/*
		**************
		DEBUG AREA
		**************
		//red north east
		drawDDALine(100, 100, 170, 30, Colour(255, 0, 0, 255));
		//blue south east
		drawDDALine(100, 100, 170, 170, Colour(0, 0, 255, 255));
		*/

		//red north east
		drawDDALine(100, 100, 170, 30, Colour(255, 0, 0, 255));
		//blue south east
		drawDDALine(100, 100, 170, 170, Colour(0, 0, 255, 255));
		//yellow north west
		drawDDALine(100, 100, 30, 30, Colour(255, 165, 0, 255));
		//green south west
		drawDDALine(100, 100, 30, 170, Colour(60, 179, 113, 255));


		//red  between north and north east
		drawDDALine(100, 100, 140, 10, Colour(128, 0, 0, 255));
		//red  between south and south east
		drawDDALine(100, 100, 140, 190, Colour(128, 0, 0, 255));
		//red  between north and north east
		drawDDALine(100, 100, 55, 10, Colour(128, 0, 0, 255));
		//red  between south and south west
		drawDDALine(100, 100, 55, 190, Colour(128, 0, 0, 255));

	};

	void DrawTask::tutorialTwoDrawing() {
		if (animeState == ANIMATION_STATE::STOP) {
			//do nothing
		} else {
			if (vectorPoints.empty()) {
				vectorPoints.push_back(Vector3(xStartPos - 50, yStartPos, 1));
				vectorPoints.push_back(Vector3(xStartPos - 50, yStartPos + 50, 1));
				vectorPoints.push_back(Vector3(xStartPos + 50, yStartPos + 50, 1));
				vectorPoints.push_back(Vector3(xStartPos + 50, yStartPos, 1));
			}

			//scale
			//for (int i = 0; i < vectorPoints.size(); i++)
			//{
			//	vectorPoints[i] =  S * vectorPoints[i];
			//}

			//rotation
			//for (int i = 0; i < vectorPoints.size(); i++)
			//{
			//	vectorPoints[i] = R * vectorPoints[i];
			//}

			/*
			* Transformation
			* P = T2 * R * T1;
			*/
			for (int i = 0; i < vectorPoints.size(); i++)
			{
				vectorPoints[i] = P1 * vectorPoints[i];
			}



			//translation
			//switch (animeState) {
			//case ANIMATION_STATE::DEFAULT:
			//	for (int i = 0; i < vectorPoints.size(); i++)
			//	{
			//		vectorPoints[i] =   T2 * vectorPoints[i];
			//	}
			//	break;
			//case ANIMATION_STATE::FORWARD:
			//	for (int i = 0; i < vectorPoints.size(); i++)
			//	{
			//		vectorPoints[i] = T2 * vectorPoints[i];
			//	}
			//	break;
			//case ANIMATION_STATE::BACKWARD:
			//	for (int i = 0; i < 4; i++)
			//	{
			//		vectorPoints[i] =   T1 * vectorPoints[i];
			//	}
			//	break;
			//}
			//if (vectorPoints[0].x < xStartPos - 50 || vectorPoints[0].y < yStartPos) {
			//	animeState = ANIMATION_STATE::FORWARD;
			////reset to original position
			//}else if(vectorPoints[0].x > 1024 || vectorPoints[0].y > 512) {
			//	animeState = ANIMATION_STATE::BACKWARD;
			//}


			for (int j = 0; j < vectorPoints.size(); j++)
			{
				drawDDALine(vectorPoints[j].x, vectorPoints[j].y, vectorPoints[(j + 1) % 4].x, vectorPoints[(j + 1) % 4].y, Colour(60, 179, 113, 255));
			}
		}

	}
	void DrawTask::praticeLabTest() {
		Vector3 offset = Vector3(100, 100, 1);

		//points[0] = Vector3(xStartPos - 50, yStartPos -50, 1);
		//points[1] = Vector3(xStartPos - 50, yStartPos + 50, 1);
		//points[2] = Vector3(xStartPos + 50, yStartPos + 50, 1);
		//points[3] = Vector3(xStartPos + 50, yStartPos - 50, 1);
		if (vectorPoints.empty()) {
			vectorPoints.push_back(Vector3(0 + offset.x, 0 + offset.y, 1));
			vectorPoints.push_back(Vector3(0 + offset.x, 100 + offset.y, 1));
		}

		for (int i = 0; i < vectorPoints.size(); i++)
		{
			vectorPoints[i] = P * vectorPoints[i];
		}

		for (int j = 0; j < vectorPoints.size(); j++)
		{
			drawDDALine(vectorPoints[j].x, vectorPoints[j].y, vectorPoints[(j + 1) % 2].x, vectorPoints[(j + 1) % 2].y, Colour(60, 179, 113, 255));
		}

		//drawDDALine(0 + offset.x, 0+ offset.y, 100 + offset.x, 0 + offset.y,  Colour(60, 179, 113, 255));
	}

	void DrawTask::drawPencil(int x1, int y1, int x2, int y2, int r, int d) {
		float  x, y;
		int ySquare;
		int y3 = r * cos(45 * Math::DEG2RAD);
		int  rSquare = r * r;

		if (points.empty()) {
			points.push_back(Vector3(x2 - 100, y2, 1));
			points.push_back(Vector3(x1, y1, 1));
			points.push_back(Vector3(x2, y2, 1));
		}

		std::vector<Vector3> bodyVector;
		bodyVector.push_back(Vector3(462, 270, 1));
		bodyVector.push_back(Vector3(562, 270, 1));
		bodyVector.push_back(Vector3(562, 100, 1));
		bodyVector.push_back(Vector3(462, 100, 1));

		for (int j = 0; j < points.size(); j++)
		{
			drawDDALine(points[j].x, points[j].y, points[(j + 1) % points.size()].x, points[(j + 1) % points.size()].y, Colour(0, 0, 0, 255));
		}

		for (int k = 0; k < bodyVector.size(); k++)
		{
			drawDDALine(bodyVector[k].x, bodyVector[k].y, bodyVector[(k + 1) % bodyVector.size()].x, bodyVector[(k + 1) % bodyVector.size()].y, Colour(0, 0, 0, 255));
		}

		//the top part - upper half circle
		Colour c = Colour(255, 0, 0, 255);
		int cx = 462 + (562 - 462) / 2, cy = 100;
		r = 50;

		for (y = 0; y <= r / sqrt(2); y++) {
			x = sqrt(r * r - y * y);
			//border circle
			//upper border circle cy -
			drawArea->plotPixel(cx - y, cy - x, c);
			drawArea->plotPixel(cx + x, cy - y, c);
			drawArea->plotPixel(cx + y, cy - x, c);
			drawArea->plotPixel(cx - x, cy - y, c);

			////Upper filled circle
			////0 - 45 degree
			//drawDDALine(cx, cy, cx - x, cy - y, c);
			////45 - 90 degree
			//drawDDALine(cx, cy, cx - y, cy - x, c);
			////90 - 135 degree
			//drawDDALine(cx, cy, cx + y, cy - x, c);
			////135 - 180 degree 
			//drawDDALine(cx, cy, cx + x, cy - y, c);
		}
		//fill body color
		int bodyStartX = 462, bodyStartY = 100, bodyEndX = 562, bodyEndY = 100, loopEnd = 270-100;
		for (int l = 0; l < loopEnd; l++) {
			drawDDALine(bodyStartX , bodyStartY+l, bodyEndX , bodyEndY+l, Colour(0, 0, 0, 255));
		}

		//fill the downward triangle with color
		int abodyStartX = 462, abodyStartY = 270, abodyEndX = 562, abodyEndY = 270, aloopEnd = 512 - 462;
		for (int m = 0; m < aloopEnd; m++) {
			drawDDALine(abodyStartX + m, abodyStartY + m, abodyEndX - m, abodyEndY + m, Colour(0, 255, 0, 255));
		}

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
		pixelPlotQueue.push_back(Pixel{ x, y, colour });
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
		for (auto& Pixel : pixelPlotQueue)
		{
			bool PixelWithinWidth = (Pixel.x >= 0 && Pixel.x < drawArea->getWidth());
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
						Pixel.x, PixelWithinWidth ? "OK" : "ERROR",
						PixelWithinWidth ? "" : " <<<\n",
						app->getRenderer()->WindowHeight,
						Pixel.y, PixelWithinHeight ? "OK" : "ERROR",
						PixelWithinHeight ? "" : " <<<\n");
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

