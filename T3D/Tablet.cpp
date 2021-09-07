#include "Tablet.h"
#include "Math.h"

namespace T3D
{
	Tablet::Tablet(Vector3 size, float bezel_width, float corner_radius, float screen_depression, int density)
	{
		int d = 6;
		// Init vertex and index arrays
		int sideTopStart = 0;

		//since the top cap will use 7 verticies, the bottom start needs to +1
		int sideBottomStart = d + 1;
		//body + (6 triangles - 6 verticies on the side + 1 center point)

		initArrays((d * 2) + ((2+2)),	// num vertices
			12,		// num tris - top + bottom
		8);		// num quads

		// Set vertices
		float theta = 0;
		//bottom-right corner center point
		//todo - x = (size.x / 2) - bezel_width
		//todo - z = (size.z / 2) - bezel_width
		Vector3 bottomCenterPoint = Vector3((size.x / 2) - bezel_width, size.y , (size.z / 2) - bezel_width);

		//90 degree
		float dTheta = (Math::PI/2) / (d +1);
		int bottomIndex = 0;
		for (int i = 0; i < d+1; i++) {
			theta = i * dTheta;
			//
			float x = corner_radius * cos(theta);
			float z = corner_radius * sin(theta);

			// top vertex
			//todo - setVertex(i, center point + x, h, z);
			setVertex(i, x, size.y, z);
			
			// bottom vertex 
			bottomIndex = (d +2) + i;
			setVertex(bottomIndex, x, -size.y, z);
		}
		//top cap origin point 18
		//todo - x = (size.x / 2) - bezel_width
		//todo - z = (size.y / 2) - bezel_width
		setVertex(7, 0, size.y, 0);
		//setVertex(7, bottomCenterPoint.x, size.y, bottomCenterPoint.z);

		//bottom cap origin point 25
		setVertex(15, 0, -size.y, 0);
		//setVertex(15, bottomCenterPoint.x, -size.y, bottomCenterPoint.z);


		setTriFace(0, 0, 7, 1);
		setTriFace(1, 1, 7, 2);
		setTriFace(2, 2, 7, 3);
		setTriFace(3, 3, 7, 4);
		setTriFace(4, 4, 7, 5);
		setTriFace(5, 5, 7, 6);

		setTriFace(6, 8,   15, 9);
		setTriFace(7, 9,   15, 10);
		setTriFace(8, 10,  15, 11);
		setTriFace(9, 11,  15, 12);
		setTriFace(10, 12, 15, 13);
		setTriFace(11, 13, 15, 14);

		setQuadFace(0, 0, 1,  9,   8);
		setQuadFace(1, 1, 2,  10,  9);
		setQuadFace(2, 2, 3,  11,  10);
		setQuadFace(3, 3, 4,  12,  11);
		setQuadFace(4, 4, 5,  13,  12);
		setQuadFace(5, 5, 6, 14, 13);

		setQuadFace(6, 15, 8,  0,  7);
		setQuadFace(7, 7, 6, 14, 15);

		//setTriFace(0, 0, 6, 1);
		//setTriFace(1, 1, 6, 2);
		//setTriFace(2, 2, 6, 3);
		//setTriFace(3, 3, 6, 4);
		//setTriFace(4, 4, 6, 5);
		//setTriFace(5, 7, 13, 8);
		//setTriFace(6, 8, 13, 9);
		//setTriFace(7, 9, 13, 10);
		//setTriFace(8, 10, 13, 11);
		//setTriFace(9, 11, 13, 12);
		//setQuadFace(0, 0, 1, 8, 7);
		//setQuadFace(1, 1, 2, 9, 8);
		//setQuadFace(2, 2, 3, 10, 9);
		//setQuadFace(3, 3, 4, 11, 10);
		//setQuadFace(4, 4, 5, 12, 11);
		//setQuadFace(5, 13, 7, 0, 6);
		//setQuadFace(6, 6, 5, 12, 13);


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