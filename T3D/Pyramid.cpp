#include "Pyramid.h"

namespace T3D
{
	Pyramid::Pyramid(float size)
	{
		// Init vertex and index arrays
		
		//vertices = 1 quad base + 3 verticies / points * 4 sides
		initArrays(4 + 3 * 4,	// num vertices
			4,		// num tris
			1);		// num quads

		// Set vertices
		int pos = 0;

		//front
		setVertex(0, -size, 0, size);
		setVertex(1, size, 0, size);
		setVertex(2, 0, size, 0);

		//back
		setVertex(3, -size, 0, -size);
		setVertex(4, size, 0, -size);
		setVertex(5, 0, size, 0);

		//left
		setVertex(6, -size, 0, -size);
		setVertex(7, -size, 0, size);
		setVertex(8, 0, size, 0);

		//right
		setVertex(9, size, 0, size);
		setVertex(10, size, 0, -size);
		setVertex(11, 0, size, 0);

		//bottom
		setVertex(12, -size, 0, -size);
		setVertex(13, -size, 0, size);
		setVertex(14, size, 0, size);
		setVertex(15, size, 0, -size);



		// Build faces
		pos = 0;
		//front
		setTriFace(pos++, 0, 1, 2);
		//back
		setTriFace(pos++, 5, 4, 3);
		//left
		setTriFace(pos++, 6, 7, 8);
		//right
		setTriFace(pos++, 9, 10, 11);
		//bottom
		 setQuadFace(0, 15, 14, 13, 12);

		// Check vertex and index arrays
		checkArrays();

		// Calculate normals
		calcNormals();

	}

}