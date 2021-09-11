// =========================================================================================
// KXG363 - Advanced Games Programming, 2012
// =========================================================================================
//
// Author: Robert Ollington
//
// Sweep.cpp
//
// Create 3D meshes procedurally by moving ('sweeping') a 2D profile through space.

#include "Sweep.h"

namespace T3D
{
	/*
	 * \param points	Container of points defining a profile
	 * \param path		Path in world space to sweep profile along 
	 * \param closed	Loop the end of path back to beginning or not
	 */
    Sweep::Sweep(std::vector<Vector3>& profilePoints, SweepPath& path, bool closed) : Mesh()
    {
        const uint32_t pp = path.size();
        const uint32_t vp = profilePoints.size();
        int numVerts = pp * vp;
        int numQuads = (pp - 1) * vp;
        if (closed) numQuads += vp;
        initArrays(numVerts, 0, numQuads);
        int vpos = 0;
        int fpos = 0;
        for (uint32_t i = 0; i < pp; i++) {
            for (uint32_t j = 0; j < vp; j++) {
                Vector3 v = path[i].transformPoint(profilePoints[j]);
                setVertex(vpos++, v.x, v.y, v.z);
            }
        }
        int quadloops = pp - 1;
        if (closed) quadloops++;
        for (uint32_t i = 0; i < quadloops; i++) {
            for (uint32_t j = 0; j < vp; j++) {
                setQuadFace(fpos++,
                    (j + 0) + (i + 0) * vp,
                    (j + 1) % vp + (i + 0) * vp,
                    (j + 1) % vp + ((i + 1) % pp) * vp,
                    (j + 0) + ((i + 1) % pp) * vp);
            }
        }
        checkArrays();
        calcNormals();
        int pos = 0;
        for (int i = 0; i < numVerts; i++) {
            colors[pos++] = 1; colors[pos++] = 0; colors[pos++] = 1; colors[pos++] = 1;
        }
    }

}
