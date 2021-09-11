#include "Rectangle.h"

#include "GameObject.h"
#include "Camera.h"
#include "Light.h"
#include "Component.h"
#include "Transform.h"
#include "GLRenderer.h"
#include "KeyboardController.h"
#include "Input.h"
#include "Math.h"
#include "Cube.h"
#include "Pyramid.h"
#include "Cylinder.h"
#include "Sweep.h"
#include "SweepPath.h"


namespace T3D
{
	Rectangle::Rectangle(Vector3 size) {
		{
			initArrays((4*2),    // num vertices
				0,        // num tris - top + bottom
				6);        // num quads + screen depression quads (5) + tablet frame quads(13)

			setVertex(0, -size.x, size.y, -size.z);
			setVertex(1, size.x, size.y, -size.z);
			setVertex(2, size.x, size.y, size.z);
			setVertex(3, -size.x, size.y, size.z);

			setVertex(4, -size.x, -size.y, -size.z);
			setVertex(5, size.x,  -size.y, -size.z);
			setVertex(6, size.x,  -size.y, size.z);
			setVertex(7, -size.x, -size.y, size.z);

			setQuadFace(0, 0,3, 2, 1);
			setQuadFace(1, 4, 5, 6, 7);

			setQuadFace(2, 3, 7, 6, 2);
			setQuadFace(3, 2, 6, 5, 1);
			setQuadFace(4, 1, 5, 4, 0);
			setQuadFace(5, 0, 4, 7, 3);

			// Check vertex and index arrays
			checkArrays();

			// Calculate normals
			calcNormals();
		}
	}

}