#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "AEEngine.h"
#include "Vector2D.h"
#include "Matrix2D.h"

typedef struct GameObjectInstance GameObjectInstance;

typedef struct Shape
{
	unsigned long			mType;				// Object type (Ship, bullet, etc..)
	AEGfxVertexList*		mpMesh;				// This will hold the triangles which will form the shape of the object

}Shape;

typedef struct Component_Sprite
{
	Shape *mpShape;
	GameObjectInstance *	mpOwner;			// This component's owner
}Component_Sprite;

typedef struct Component_Transform {

	Vector2D					mPosition;			// Current position
	float					mAngle;				// Current angle
	float					mScaleX;			// Current X scaling value
	float					mScaleY;			// Current Y scaling value

	Matrix2D					mTransform;			// Object transformation matrix: Each frame, calculate the object instance's transformation matrix and save it here

	GameObjectInstance *	mpOwner;			// This component's owner
}Component_Transform;

typedef struct Component_Physics
{
	Vector2D					mVelocity;			// Current velocity

	GameObjectInstance *	mpOwner;			// This component's owner
}Component_Physics;

typedef struct Component_Target {

	GameObjectInstance *		mpTarget;		// Target, used by the homing missile
	GameObjectInstance *		mpOwner;		// This component's owner

}Component_Target;

struct GameObjectInstance
{
	unsigned long				mFlag;						// Bit mFlag, used to indicate if the object instance is active or not

	Component_Sprite			*mpComponent_Sprite;		// Sprite component
	Component_Transform			*mpComponent_Transform;		// Transform component
	Component_Physics			*mpComponent_Physics;		// Physics component
	Component_Target			*mpComponent_Target;		// Target component, used by the homing missile
};

#endif