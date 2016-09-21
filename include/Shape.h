#ifndef SHAPE_H
#define SHAPE_H

#include "AEGraphics.h"

typedef struct Shape
{
	unsigned long			mType;				// Object type (Ship, bullet, etc..)
	AEGfxVertexList*		mpMesh;				// This will hold the triangles which will form the shape of the object

}Shape;		

#endif