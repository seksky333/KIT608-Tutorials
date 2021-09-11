#include "Tablet.h"
#include "Math.h"

namespace T3D
{
	Tablet::Tablet(Vector3 size, float bezel_width, float corner_radius, float screen_depression, int density)
	{
		/*
		* ***
		* This design is based on the density is 6
		* ***
		*/

		int d = density;
		// Init vertex and index arrays
		int sideTopStart = 0;
		const int bodyCornerVerticies = d *2;
		//since the top cap will use 7 verticies, the bottom start needs to +1
		int sideBottomStart = d + 1;
		//body (6 triangles - 6 verticies on the side + 2 extra verticies for the body + 2 points for the center of the top and the bottom )
		initArrays((bodyCornerVerticies * 4) + (4 * 2) + (4 * 2),    // num vertices
			bodyCornerVerticies * 4,        // num tris - top + bottom
			d * 4);        // num quads

		/*
		* 1.Creating points for the corner's body
		*/
		
		//+-
		Vector3 centerPoint = Vector3((size.x / 2) - bezel_width, -size.y, (size.z / 2) - bezel_width);
		float halfBezelWidth = bezel_width / 2;
		float theta = 0;

		//90 degree
		float dTheta = (Math::PI/2) / (d +1);
		const int dVerticies = d + 1;//7
		int bottomRightBottomIndex = 0;

		int topRightTopIndex = 0;
		int topRightBottomIndex = 0;

		int topLeftTopIndex = 0;
		int topLeftBottomIndex = 0;

		int bottomLeftTopIndex = 0;
		int bottomLeftBottomIndex = 0;
		for (int i = 0; i < d+1; i++) {
			theta = i * dTheta;
			float x = corner_radius * cos(theta);
			float z = corner_radius * sin(theta);

			// bottom-right top verticies
			setVertex(i, (centerPoint.x + halfBezelWidth) + x, size.y, (centerPoint.z + halfBezelWidth) + z);
			// bottom-right bottom verticies 
			bottomRightBottomIndex = (dVerticies +1);//8
			setVertex(bottomRightBottomIndex + i, (centerPoint.x + halfBezelWidth) + x, -size.y, (centerPoint.z + halfBezelWidth) + z);

			// top-right top verticies
			topRightTopIndex = (dVerticies * 2) + 2;//16
			setVertex(topRightTopIndex + i, (centerPoint.x + halfBezelWidth) + x, size.y, (-centerPoint.z - halfBezelWidth) - z);
			// top-right bottom verticies
			topRightBottomIndex = (dVerticies * 3) + 3;//24
			setVertex(topRightBottomIndex + i, (centerPoint.x + halfBezelWidth) + x, -size.y, (-centerPoint.z - halfBezelWidth) - z);

			//top-left top verticies
			topLeftTopIndex = (dVerticies * 4) + 4;//32
			setVertex(topLeftTopIndex + i, (-centerPoint.x - halfBezelWidth) - x, size.y, (-centerPoint.z - halfBezelWidth) - z);
			//top-left bottom verticies
			topLeftBottomIndex = (dVerticies * 5) + 5;//40
			setVertex(topLeftBottomIndex + i, (-centerPoint.x - halfBezelWidth) - x, -size.y, (-centerPoint.z - halfBezelWidth) - z);

			//bottom-left top verticies
			bottomLeftTopIndex = (dVerticies * 6) + 6;//48
			setVertex(bottomLeftTopIndex + i, (-centerPoint.x - halfBezelWidth) - x, size.y, (centerPoint.z + halfBezelWidth) + z);

			//bottom-left bottom verticies
			bottomLeftBottomIndex = (dVerticies * 7) + 7;//56
			setVertex(bottomLeftBottomIndex + i, (-centerPoint.x - halfBezelWidth) - x, -size.y, (centerPoint.z + halfBezelWidth) + z);
		}
		/*
		* 2.Creating center points for the corner's body
		*/

		//top cap origin point 18
		//setVertex(7, 0, size.y, 0);
		//0 - 6 (7vectices for the corner a top body)
		//7
		const int bottomRightCornerTopCentreVertex = dVerticies;
		setVertex(bottomRightCornerTopCentreVertex, centerPoint.x, size.y, centerPoint.z);

		//bottom cap origin point 25
		//8 - 14 (7 vectices for the corner a bottom body)
		//15
		const int aCornerBottomCentreVertex = (dVerticies * 2)+1;
		setVertex(aCornerBottomCentreVertex, centerPoint.x, -size.y, centerPoint.z);

		//16 - 22 (7 vectices for the corner b top body)
		//23
		const int topRightCornerTopCentreVertex = (dVerticies * 3) +2;
		setVertex(topRightCornerTopCentreVertex , centerPoint.x, size.y, -centerPoint.z);

		//24 - 30 (7 vectices for the corner b bottom body)
		//31
		const int topRightCornerBottomCentreVertex = (dVerticies * 4) +3;
		setVertex(topRightCornerBottomCentreVertex, centerPoint.x, -size.y, -centerPoint.z);

		//32 - 38 (7 vectices for the corner c top body)
		//39
		const int topLeftCornerTopCentreVertex = (dVerticies * 5) + 4;
		setVertex(topLeftCornerTopCentreVertex, -centerPoint.x, size.y, -centerPoint.z);

		//40 - 46 (7 vectices for the corner c bottom body)
		//47
		const int topLeftCornerBottomCentreVertex = (dVerticies * 6) + 5;
		setVertex(topLeftCornerBottomCentreVertex, -centerPoint.x, -size.y, -centerPoint.z);


		//48 - 54 (7 vectices for the corner d top body)
		//55
		const int bottoomLeftCornerTopCentreVertex = (dVerticies * 7) + 6;
		setVertex(bottoomLeftCornerTopCentreVertex, -centerPoint.x, size.y, centerPoint.z);

		//56 - 62 (7 vectices for the corner d bottom body)
		//63
		const int bottomLeftCornerBottomCentreVertex = (dVerticies * 8) + 7;
		setVertex(bottomLeftCornerBottomCentreVertex, -centerPoint.x, -size.y, centerPoint.z);


		/*
		* 3.Creating faces
		*/
		//a corner = bottom-right corner
		const int aCornerBottomCap1Point = d + 3;
		const int aCornerBottomCap3Point = d + 2;
		const int aCornerQuad3Point = d + 3;
		const int aCornerQuad4Point = d + 2;

		//b coorner = top-right corner
		const int bCornerTopCapTriBaseIndex = d * 2;//12
		const int bCornerTopCap1Point = bCornerTopCapTriBaseIndex + 5; //17
		const int bCornerTopCap3Point = bCornerTopCapTriBaseIndex + 4; //16

		const int bCornerBottomCapTriBaseIndex = d * 3;//18
		const int bCornerBottomCap1Point = bCornerBottomCapTriBaseIndex + 6; //24
		const int bCornerBottomCap3Point = bCornerBottomCapTriBaseIndex + 7; //25
		
		const int bCornerQuadCapBaseIndex = d;//6
		const int bCornerQuadCap1Point = bCornerQuadCapBaseIndex + 10; //16
		const int bCornerQuadCap2Point = bCornerQuadCapBaseIndex + 18; //24
		const int bCornerQuadCap3Point = bCornerQuadCapBaseIndex + 19; //25
		const int bCornerQuadCap4Point = bCornerQuadCapBaseIndex + 11; //17
		
		//c coorner = top-left corner
		const int cCornerTopCapTriBaseIndex = d * 4;//24
		const int cCornerTopCap1Point = cCornerTopCapTriBaseIndex + 8; //32
		const int cCornerTopCap3Point = cCornerTopCapTriBaseIndex + 9; //33
		
		const int cCornerBottomCapTriBaseIndex = d * 5;//30
		const int cCornerBottomCap1Point = cCornerBottomCapTriBaseIndex + 12; //25
		const int cCornerBottomCap3Point = cCornerBottomCapTriBaseIndex + 11; //24
		
		const int cCornerQuadCapBaseIndex = d*2;//12
		const int cCornerQuadCap1Point = cCornerQuadCapBaseIndex + 20; //32
		const int cCornerQuadCap2Point = cCornerQuadCapBaseIndex + 21; //33
		const int cCornerQuadCap3Point = cCornerQuadCapBaseIndex + 29; //41
		const int cCornerQuadCap4Point = cCornerQuadCapBaseIndex + 28; //40

		//d coorner = bottom-left corner
		const int dCornerTopCapTriBaseIndex = d * 6;//36
		const int dCornerTopCap1Point = dCornerTopCapTriBaseIndex + 13; //48
		const int dCornerTopCap3Point = dCornerTopCapTriBaseIndex +12; //49

		const int dCornerBottomCapTriBaseIndex = d * 7;//42
		const int dCornerBottomCap1Point = dCornerBottomCapTriBaseIndex + 14; //56
		const int dCornerBottomCap3Point = dCornerBottomCapTriBaseIndex + 15; //57

		const int dCornerQuadCapBaseIndex = d * 3;//18
		const int dCornerQuadCap1Point = dCornerQuadCapBaseIndex + 30; //48
		const int dCornerQuadCap2Point = dCornerQuadCapBaseIndex + 38; //56
		const int dCornerQuadCap3Point = dCornerQuadCapBaseIndex + 39; //57
		const int dCornerQuadCap4Point = dCornerQuadCapBaseIndex + 31; //49

		for (int i = 0; i < d; i++)
		{	
			//bottom-right corner
			//0, 6
			setTriFace(i, i, bottomRightCornerTopCentreVertex, i+1);
			setTriFace(d + i, aCornerBottomCap1Point + i, aCornerBottomCentreVertex, aCornerBottomCap3Point + i);
			setQuadFace(i, i, i + 1, aCornerQuad3Point + i , aCornerQuad4Point + i);
			
			//top-right corner
			//12 + i, 17 + i, 23, 16 + i
			setTriFace(bCornerTopCapTriBaseIndex+i, bCornerTopCap1Point+i, topRightCornerTopCentreVertex, bCornerTopCap3Point+i);
			//18 + i, 24 + i, 31, 25 + i
			setTriFace(bCornerBottomCapTriBaseIndex + i, bCornerBottomCap1Point + i, topRightCornerBottomCentreVertex, bCornerBottomCap3Point + i);
			//6 + i, 16 + i, 24 + i, 25 + i, 17 + i
			setQuadFace(bCornerQuadCapBaseIndex + i, bCornerQuadCap1Point + i, bCornerQuadCap2Point + i, bCornerQuadCap3Point + i, bCornerQuadCap4Point + i);

			//top-left corner
			//24 + i, 33 + i, 39, 32 + i
			setTriFace(cCornerTopCapTriBaseIndex + i, cCornerTopCap1Point + i, topLeftCornerTopCentreVertex, cCornerTopCap3Point + i);
			//30 + i, 41 + i, 47, 42 + i
			setTriFace(cCornerBottomCapTriBaseIndex + i, cCornerBottomCap1Point + i, topLeftCornerBottomCentreVertex, cCornerBottomCap3Point + i);
			//12 + i, 32 + i, 33 + i, 41 + i, 40 + i
			setQuadFace(cCornerQuadCapBaseIndex + i, cCornerQuadCap1Point + i, cCornerQuadCap2Point + i, cCornerQuadCap3Point + i, cCornerQuadCap4Point + i);

			//bottom-left corner
			//36 + i, 49 + i, 55, 48 + i
			setTriFace(dCornerTopCapTriBaseIndex + i, dCornerTopCap1Point + i, bottoomLeftCornerTopCentreVertex, dCornerTopCap3Point + i);
			//42 + i, 56 + i, 63, 57 + i
			setTriFace(dCornerBottomCapTriBaseIndex + i, dCornerBottomCap1Point + i, bottomLeftCornerBottomCentreVertex, dCornerBottomCap3Point + i);
			//18 + i, 48 + i, 56 + i, 57 + i, 49 + i
			setQuadFace(dCornerQuadCapBaseIndex + i, dCornerQuadCap1Point + i, dCornerQuadCap2Point + i, dCornerQuadCap3Point + i, dCornerQuadCap4Point + i);
		}
		//Corner D
		//setTriFace(36, 49, bottomLeftCornerTopCentreVertex, 48);
		//setTriFace(42, 56, bottomLeftCornerBottomCentreVertex, 57);
		//setQuadFace(18, 48, 56, 57, 49);

		//Corner C
		//setTriFace(24, 32, topLeftCornerTopCentreVertex, 33);
		//setTriFace(30, 42, topLeftCornerBottomCentreVertex, 41);
		//setQuadFace(12, 32, 33, 41, 40);
		
		//Corner B
		//setTriFace(12, 17, topRightCornerTopCentreVertex, 16);
		//setTriFace(13, 18, topRightCornerTopCentreVertex, 17);
		//setTriFace(14, 19, topRightCornerTopCentreVertex, 18);
		//setTriFace(15, 20, topRightCornerTopCentreVertex, 19);
		//setTriFace(16, 21, topRightCornerTopCentreVertex, 20);
		//setTriFace(17, 22, topRightCornerTopCentreVertex, 21);

		//setTriFace(18, 24, topRightCornerBottomCentreVertex, 25);
		//setTriFace(19, 25, topRightCornerBottomCentreVertex, 26);
		//setTriFace(20, 26, topRightCornerBottomCentreVertex, 27);
		//setTriFace(21, 27, topRightCornerBottomCentreVertex, 28);
		//setTriFace(22, 28, topRightCornerBottomCentreVertex, 29);
		//setTriFace(23, 29, topRightCornerBottomCentreVertex, 30);

		//setQuadFace(6,  16,  24,  25,   17);
		//setQuadFace(7, 17, 25, 26, 18);
		//setQuadFace(8, 18, 26, 27, 19);
		//setQuadFace(9, 19, 27, 28, 20);
		//setQuadFace(10, 20, 28, 29, 21);
		//setQuadFace(11, 21, 29, 30, 22);

		//Corner A
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
		// 
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