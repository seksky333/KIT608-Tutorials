#include "Tablet.h"
#include "Math.h"

namespace T3D
{
	Tablet::Tablet(Vector3 size, float bezel_width, float corner_radius, float screen_depression, int density)
	{
		int d = density;
		// Init vertex and index arrays
		int sideTopStart = 0;

		//since the top cap will use 7 verticies, the bottom start needs to +1
		int sideBottomStart = d + 1;
		//body + (6 triangles - 6 verticies on the side + 1 center point)
		initArrays((d * 4) + (4 * 2),    // num vertices
			d*4,        // num tris - top + bottom
			d*2);        // num quads

		//initArrays((d * 2) + (4* 1),	// num vertices
		//	d*2,		// num tris - top + bottom
		//d);		// num quads
		
		//+-
		Vector3 centerPoint = Vector3((size.x / 2) - bezel_width, -size.y, (size.z / 2) - bezel_width);
		float halfBezelWidth = bezel_width / 2;
		float theta = 0;

		//90 degree
		float dTheta = (Math::PI/2) / (d +1);
		const int dVerticies = d + 1;
		int bottomRightBottomIndex = 0;
		int topRightTopIndex = 0;
		int topRightBottomIndex = 0;
		for (int i = 0; i < d+1; i++) {
			theta = i * dTheta;
			float x = corner_radius * cos(theta);
			float z = corner_radius * sin(theta);

			// bottom-right top vertex
			setVertex(i, (centerPoint.x + halfBezelWidth) + x, size.y, (centerPoint.z + halfBezelWidth) + z);
			
			// bottom-right bottom vertex 
			bottomRightBottomIndex = (dVerticies +1);//8
			setVertex(bottomRightBottomIndex + i, (centerPoint.x + halfBezelWidth) + x, -size.y, (centerPoint.z + halfBezelWidth) + z);

			// top-right top vertex
			topRightTopIndex = (dVerticies * 2) + 2;//16
			setVertex(topRightTopIndex + i, (centerPoint.x + halfBezelWidth) + x, size.y, (-centerPoint.z - halfBezelWidth) - z);
			
			// top-right bottom vertex
			topRightBottomIndex = (dVerticies * 3) + 3;//24
			setVertex(topRightBottomIndex + i, (centerPoint.x + halfBezelWidth) + x, -size.y, (-centerPoint.z - halfBezelWidth) - z);
		}

		//top cap origin point 18
		//setVertex(7, 0, size.y, 0);
		//0 - 6 (7vectices for the 1 top body)
		//7
		const int bottomRightCornerTopCentreVertex = dVerticies;
		setVertex(bottomRightCornerTopCentreVertex, centerPoint.x, size.y, centerPoint.z);

		//bottom cap origin point 25
		//8 - 14 (7 vectices for the 1 bottom body)
		//15
		const int aCornerBottomCentreVertex = (dVerticies * 2)+1;
		setVertex(aCornerBottomCentreVertex, centerPoint.x, -size.y, centerPoint.z);

		//16 - 22 (7 vectices for the 2 top body)
		//23
		const int topRightCornerTopCentreVertex = (dVerticies * 3) +2;
		setVertex(topRightCornerTopCentreVertex , centerPoint.x, size.y, -centerPoint.z);

		//24 - 30 (7 vectices for the 2 bottom body)
		//31
		const int topRightCornerBottomCentreVertex = (dVerticies * 4) +3;
		setVertex(topRightCornerBottomCentreVertex, centerPoint.x, -size.y, -centerPoint.z);
		//a corner = bottom-right corner
		int aCornerBottomCap1Point = d + 3;
		int aCornerBottomCap3Point = d + 2;
		int aCornerQuad3Point = d + 3;
		int aCornerQuad4Point = d + 2;

		//b coorner = top-right corner
		int bCornerTopCapTriBaseIndex = d * 2;//12
		int bCornerTopCap1Point = bCornerTopCapTriBaseIndex + 5; //17
		int bCornerTopCap3Point = bCornerTopCapTriBaseIndex + 4; //16
		int bCornerBottomCapTriBaseIndex = d * 3;//18

		for (int i = 0; i < d; i++)
		{	
			//bottom-right corner
			//0, 6
			setTriFace(i, i, bottomRightCornerTopCentreVertex, i+1);
			setTriFace(d + i, aCornerBottomCap1Point + i, aCornerBottomCentreVertex, aCornerBottomCap3Point + i);
			setQuadFace(i, i, i + 1, aCornerQuad3Point + i , aCornerQuad4Point + i);

			//top-right corner
			//12
			//setTriFace(bCornerTopCapTriBaseIndex + i, bCornerTopCap1Point + i , topRightCornerTopCentreVertex, bCornerTopCap3Point + i);
			//setTriFace(bCornerBottomCapTriBaseIndex + i, bCornerTopCap1Point + i, topRightCornerTopCentreVertex, bCornerTopCap3Point + i);
			//setTriFace((d * 3) + i, (d * 3) + i + 7, topRightCornerTopCentreVertex, (d * 3) + i + 6);
			//setQuadFace(d+i, (d * 2) + i + 5,
			//	(d * 2) + i + 5 +1,
			//	(d * 2) + i + 5,
			//	(d * 2) + i + 4
			//	);
		}
		setTriFace(12, 17, topRightCornerTopCentreVertex, 16);
		setTriFace(13, 18, topRightCornerTopCentreVertex, 17);
		setTriFace(14, 19, topRightCornerTopCentreVertex, 18);
		setTriFace(15, 20, topRightCornerTopCentreVertex, 19);
		setTriFace(16, 21, topRightCornerTopCentreVertex, 20);
		setTriFace(17, 22, topRightCornerTopCentreVertex, 21);

		setTriFace(18, 24, topRightCornerBottomCentreVertex, 25);
		setTriFace(19, 25, topRightCornerBottomCentreVertex, 26);
		setTriFace(20, 26, topRightCornerBottomCentreVertex, 27);
		setTriFace(21, 27, topRightCornerBottomCentreVertex, 28);
		setTriFace(22, 28, topRightCornerBottomCentreVertex, 29);
		setTriFace(23, 29, topRightCornerBottomCentreVertex, 30);

		setQuadFace(6,  16,  24,  25,   17);
		setQuadFace(7, 17, 25, 26, 18);
		setQuadFace(8, 18, 26, 27, 19);
		setQuadFace(9, 19, 27, 28, 20);
		setQuadFace(10, 20, 28, 29, 21);
		setQuadFace(11, 21, 29, 30, 22);

		//setTriFace(0, 0, bottomRightCornerTopCentreVertex, 1);
		//setTriFace(1, 1, bottomRightCornerTopCentreVertex, 2);
		//setTriFace(2, 2, bottomRightCornerTopCentreVertex, 3);
		//setTriFace(3, 3, bottomRightCornerTopCentreVertex, 4);
		//setTriFace(4, 4, bottomRightCornerTopCentreVertex, 5);
		//setTriFace(5, 5, bottomRightCornerTopCentreVertex, 6);
		// 
		//setTriFace(6, 9,   bottomRightCornerBottomCentreVertex, 8);
		//setTriFace(7, 10,  bottomRightCornerBottomCentreVertex, 9);
		//setTriFace(8, 11,  bottomRightCornerBottomCentreVertex, 10);
		//setTriFace(9, 12,  bottomRightCornerBottomCentreVertex, 11);
		//setTriFace(10, 13, bottomRightCornerBottomCentreVertex, 12);
		//setTriFace(11, 14, bottomRightCornerBottomCentreVertex, 13);
		//setQuadFace(0, 0, 1,  9,   8);
		//setQuadFace(1, 1, 2,  10,  9);
		//setQuadFace(2, 2, 3,  11,  10);
		//setQuadFace(3, 3, 4,  12,  11);
		//setQuadFace(4, 4, 5,  13,  12);
		//setQuadFace(5, 5, 6, 14, 13);





		//for (int i = 0; i < d; i++) {
		//	setQuadFace(i,   // face id
		//		i,         // current top vertex
		//		(i + 1) % d,   // next top vertex (wrapping)
		//		d + (i + 1) % d, // next bottom vertex (wrapping) 
		//		d + i        // current bottom vertex
		//	);
		//	int topCapTriBottomVertex1 = 0;
		//	int topCapTriTopVertex1 = 0;
		//	int topCapTriBottomVertex2 = 0;

		//	topCapTriBottomVertex1 = sideTopStart + i;
		//	topCapTriTopVertex1 = d + sideTopStart;
		//	topCapTriBottomVertex2 = sideTopStart + i + 1;

			//handle the last triangle
			//if ((sideTopStart + i + 1) == d + sideTopStart) {
			//	topCapTriBottomVertex2 = sideTopStart;
			//}
			//top cap
			//setTriFace(i,   // face id
			//	topCapTriBottomVertex1,
			//	topCapTriTopVertex1, // next bottom vertex (wrapping) 
			//	topCapTriBottomVertex2
			//);

			//int bottomCapTriBottomVertex1 = 0;
			//int bottomCapTriTopVertex1 = 0;
			//int bottomCapTriBottomVertex2 = 0;

			//bottomCapTriBottomVertex1 = sideBottomStart + i;
			//bottomCapTriTopVertex1 = d + sideBottomStart;
			//bottomCapTriBottomVertex2 = sideBottomStart + i + 1;
			////handle the last triangle
			//if ((sideBottomStart + i + 1) == d + sideBottomStart) {
			//	bottomCapTriBottomVertex2 = sideBottomStart;
			//}

			//bottom cap
			//setTriFace(d + i,   // face id
			//	bottomCapTriBottomVertex2,
			//	bottomCapTriTopVertex1, // next bottom vertex (wrapping) 
			//	bottomCapTriBottomVertex1
			//);
		//}

		//setQuadFace(d, );
		//setQuadFace(d+1);

		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();


	}
}