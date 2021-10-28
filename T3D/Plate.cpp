#include "Plate.h"
#include "Math.h"

namespace T3D
{
	Plate::Plate(float ra, float ha, int da)
	{
		//int d = 24;
		//float h = 0.005;
		//float r = .5;
		int d = da;
		float h = ha;
		float r = ra;
		//inner radius
		float r1 = r * 0.8;
		// Init vertex and index arrays
		int sideTopStart = d * 2;
		//since the top cap will use 7 verticies, the bottom start needs to +1
		int sideBottomStart = d * 3 + 1;

		int innerTopStart = d * 4 + 2;
		int innerBottomStart = d * 5 + 2;

		//body + (6 triangles - 6 verticies on the side + 1 center point)

		//initArrays((d * 2) + ((d + 1) * 2),	// num vertices
		//	d * 2,		// num tris - top + bottom
		//	d);		// num quads

		initArrays((d*6)+1,	// num vertices
			d * 2,		// num tris - top + bottom
			d * 2);		// num quads + test quad

		// Set vertices
		float theta = 0;

		float dTheta = (Math::TWO_PI) / d;
		for (int i = 0; i < d; i++) {
			theta = i * dTheta;
			float x = r * cos(theta);
			float z = r * sin(theta);

			float innerX = r1 * cos(theta);
			float innerZ = r1 * sin(theta);

			// top vertex 0 - 11
			setVertex(i, x, h, z);
			setUV(i, 0.418, 0.1);
			// bottom vertex 12 - 23
			setVertex(d + i, x, -h, z);
			//top cap 24 -35
			setVertex(sideTopStart + i, x, h, z);
			setUV(sideTopStart + i, 0.418, 0.47);
			//bottom cap 37 - 48
			setVertex(sideBottomStart + i, x, -h, z);
			//printf("Counter: %d\n", i);
			//inner circle
			// top vertex 50 - 61
			setVertex(innerTopStart + i, innerX, h, innerZ);
			setUV(innerTopStart + i, 0.05, 0.47);
			// bottom vertex 62 - 73
			setVertex(innerBottomStart + i, innerX, -h, innerZ);
		}
		//top cap center point 36
		setVertex(sideTopStart + d, 0, h, 0);

		//bottom cap center point 49
		setVertex(sideBottomStart + d, 0, -h, 0);


		for (int i = 0; i < d; i++) {


			setQuadFace(i,   // face id
				i,         // current top vertex
				(i + 1) % d,   // next top vertex (wrapping)
				d + (i + 1) % d, // next bottom vertex (wrapping) 
				d + i        // current bottom vertex
			);
			//last one
			//36 = 71
			//24 = 47
			//12 = 23
			int lastRound = d*2 -1;
			if (d + i == lastRound) {
				setQuadFace(d + i,   // 12
					sideTopStart + i, // 35
					innerTopStart + i, // 61
					innerTopStart,// 50
					sideTopStart  //24
				);
			}
			else {
				setQuadFace(d + i,   // 12
					sideTopStart + i, // 24
					innerTopStart + i, // 50
					(innerTopStart + 1) + i,// 51
					(sideTopStart + 1) + i  //25
				);
			}


			int topCapTriBottomVertex1 = 0;
			int topCapTriTopVertex1 = 0;
			int topCapTriBottomVertex2 = 0;

			topCapTriBottomVertex1 = sideTopStart + i;
			topCapTriTopVertex1 = d + sideTopStart;
			topCapTriBottomVertex2 = sideTopStart + i + 1;

			//handle the last triangle
			if ((sideTopStart + i + 1) == d + sideTopStart) {
				topCapTriBottomVertex2 = sideTopStart;
			}
			////top cap
			//setTriFace(i,   // face id
			//	topCapTriBottomVertex1,
			//	topCapTriTopVertex1, // next bottom vertex (wrapping) 
			//	topCapTriBottomVertex2
			//);

			int bottomCapTriBottomVertex1 = 0;
			int bottomCapTriTopVertex1 = 0;
			int bottomCapTriBottomVertex2 = 0;

			bottomCapTriBottomVertex1 = sideBottomStart + i;
			bottomCapTriTopVertex1 = d + sideBottomStart;
			bottomCapTriBottomVertex2 = sideBottomStart + i + 1;
			//handle the last triangle
			if ((sideBottomStart + i + 1) == d + sideBottomStart) {
				bottomCapTriBottomVertex2 = sideBottomStart;
			}

			//top cap
			setTriFace(i,   // face id
				bottomCapTriBottomVertex1,
				bottomCapTriTopVertex1, // next bottom vertex (wrapping) 
				bottomCapTriBottomVertex2
			);
			////bottom cap
			//setTriFace(i,   // face id
			//	bottomCapTriBottomVertex2,
			//	bottomCapTriTopVertex1, // next bottom vertex (wrapping) 
			//	bottomCapTriBottomVertex1
			//);
			//bottom cap
			setTriFace(d + i,   // face id
				bottomCapTriBottomVertex2,
				bottomCapTriTopVertex1, // next bottom vertex (wrapping) 
				bottomCapTriBottomVertex1
			);
		}
		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();

	}

}