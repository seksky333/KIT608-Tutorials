#include "House.h"


using namespace T3D;
namespace T3D
{
	void House::init() {

	}
	House::House(float size)
	{
		//int vpos = 0;
		int uvpos = 0;



		// Init vertex and index arrays
		//cube faces + 2 for the roof
		initArrays((4 * 6) + 2,	// num vertices
			2,		// num tris - 2 tris for the roof
			(6-1) + 2);		// num quads (6 -1 (top face replaced by the roof))
							//+ 2 quads for the roof
		// Set vertices
		int pos = 0;
		//front
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, size, -size, -size);
		setVertex(pos++, size, size, -size);
		setVertex(pos++, -size, size, -size);
		setUV(uvpos++, 0.05, 0.1);
		setUV(uvpos++, 0.418, 0.1);
		setUV(uvpos++, 0.418, 0.47);
		setUV(uvpos++, 0.05, 0.47);
		//back
		setVertex(pos++, -size, -size, size);
		setVertex(pos++,  size, -size, size);
		setVertex(pos++,  size,  size, size);
		setVertex(pos++, -size, size, size);
		setUV(uvpos++, 0.05, 0.1);
		setUV(uvpos++, 0.418, 0.1);
		setUV(uvpos++, 0.418, 0.47);
		setUV(uvpos++, 0.05, 0.47);
		
		//left
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, -size,  size, -size);
		setVertex(pos++, -size,  size, size);
		setVertex(pos++, -size, -size, size);
		setUV(uvpos++, 0.418, 0.1);
		setUV(uvpos++, 0.418, 0.47);
		setUV(uvpos++, 0.05, 0.47);
		setUV(uvpos++, 0.05, 0.1);
		//right
		setVertex(pos++, size, -size, -size);
		setVertex(pos++, size, size, -size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, size, -size, size);
		setUV(uvpos++, 0.418, 0.1);
		setUV(uvpos++, 0.418, 0.47);
		setUV(uvpos++, 0.05, 0.47);
		setUV(uvpos++, 0.05, 0.1);
		//bottom
		setVertex(pos++, -size, -size, -size);
		setVertex(pos++, -size, -size, size);
		setVertex(pos++, size, -size, size);
		setVertex(pos++, size, -size, -size);
		setUV(uvpos++, 0.05, 0.1);
		setUV(uvpos++, 0.418, 0.1);
		setUV(uvpos++, 0.418, 0.47);
		setUV(uvpos++, 0.05, 0.47);
		//top
		setVertex(pos++, -size, size, -size);
		setVertex(pos++, -size, size, size);
		setVertex(pos++, size, size, size);
		setVertex(pos++, size, size, -size);
		setUV(uvpos++, 0.05, 0.1);
		setUV(uvpos++, 0.418, 0.1);
		setUV(uvpos++, 0.418, 0.47);
		setUV(uvpos++, 0.05, 0.47);

		//roof
		setVertex(24, 0, size*2, size);
		setVertex(25, 0, size*2, -size);
		//setUV(uvpos++, 0.5, 0.5);
		//setUV(uvpos++, 1, 0.5);



		//setUV(uvpos++, 1, 1);
		//setUV(uvpos++, 1, 1);

		// Build quads
		pos = 0;
		//front
		setQuadFace(pos++, 3, 2, 1, 0);
		//back
		setQuadFace(pos++, 4, 5, 6, 7);
		//left
		setQuadFace(pos++, 11, 10, 9, 8);
		//right
		setQuadFace(pos++, 12, 13, 14, 15);
		//bottom
		setQuadFace(pos++, 19, 18, 17, 16);
		//top
		//setQuadFace(pos++, 20, 21, 22, 23);

		//roof
		//triangle pos
		int triPos = 0;
		setTriFace(triPos++,22, 24, 21);
		setTriFace(triPos++, 20, 25, 23);
		setQuadFace(pos++, 25, 20, 21, 24);
		setQuadFace(pos++, 24, 22, 23, 25);
		

		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();

		 //Setup other arrays		
		//pos = 0;
		//front
		//for (int i = 0; i < 4; i++) {
		//	colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1;
		//}
		////back
		//for (int i = 0; i < 4; i++) {
		//	colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1;
		//}
		////left
		//for (int i = 0; i < 4; i++) {
		//	colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1;
		//}
		////right
		//for (int i = 0; i < 4; i++) {
		//	colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1;
		//}
		////bottom
		//for (int i = 0; i < 4; i++) {
		//	colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
		//}
		////top
		//for (int i = 0; i < 4; i++) {
		//	colors[pos++] = 0; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
		//}



		//uvs
		//pos = 0;
		//for (int f = 0; f < 6; f++) {
		//	uvs[pos++] = 0; uvs[pos++] = 0;
		//	uvs[pos++] = 0; uvs[pos++] = 1;
		//	uvs[pos++] = 1; uvs[pos++] = 1;
		//	uvs[pos++] = 1; uvs[pos++] = 0;
		//}
	}
}
