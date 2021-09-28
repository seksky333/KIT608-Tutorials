#include "TCylinder.h"
#include "Math.h"


using namespace T3D;
namespace T3D
{
	void TCylinder::init() {

	}
	TCylinder::TCylinder(float r, float h, int d)
	{

		// Init vertex and index arrays
		int sideTopStart = (d+1) * 2;
		//since the top cap will use 7 verticies, the bottom start needs to +1
		int sideBottomStart = (d+1) * 3 ;
		//body + (6 triangles - 6 verticies on the side + 1 center point)
		initArrays(((d+1) * 2) + ((d + 1) * 2),	// num vertices
			d * 2,		// num tris - top + bottom
			d);		// num quads

		// Set vertices
		

		for (float i = 0; i <= d; i++) {
			float theta = float(i) / d * (Math::TWO_PI);

			float x = r * cos(theta);
			float z = r * sin(theta);

			// top vertex
			setVertex(i, x, h, z);

			// bottom vertex 
			setVertex( (d + 1) + i, x, -h, z);

			//top cap 12
			setVertex(sideTopStart + i, x, h, z);

			//bottom cap 19
			setVertex(sideBottomStart + i, x, -h, z);
		}
		//top cap center point 18
		setVertex(sideTopStart + d, 0, h, 0);

		//bottom cap center point 25
		setVertex(sideBottomStart + d, 0, -h, 0);



		for (int i = 0; i < d; i++) {
			setQuadFace(i,   // face id
				i,         // current top vertex
				(i + 1),   // next top vertex (wrapping)
				(d+1) + (i + 1), // next bottom vertex (wrapping) 
				(d+1) + i        // current bottom vertex
			);
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
			//top cap
			setTriFace(i,   // face id
				topCapTriBottomVertex1,
				topCapTriTopVertex1, // next bottom vertex (wrapping) 
				topCapTriBottomVertex2
			);

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
