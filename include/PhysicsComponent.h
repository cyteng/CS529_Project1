#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "Vector2D.h"
#include "GameObjectInstance.h"

#define SHIP_ACCEL_FORWARD			50.0f				// Ship forward acceleration (in m/s^2)
#define SHIP_ACCEL_BACKWARD			-100.0f				// Ship backward acceleration (in m/s^2)
#define SHIP_ROT_SPEED				(2.0f * PI)			// Ship rotation speed (radian/second)

enum SHIP_MOVEMENT_TYPE
{
	// list of game object types
	SHIP_MOVEMENT_TYPE_ACCEL_FORWARD = 0,
	SHIP_MOVEMENT_TYPE_ACCEL_BACKWARD,
	SHIP_MOVEMENT_TYPE_ROT_LEFT,
	SHIP_MOVEMENT_TYPE_ROT_RIGHT,

	SHIP_MOVEMENT_NUM,
};

struct Component_Physics
{
	Vector2D					mVelocity;			// Current velocity

	GameObjectInstance *	mpOwner;			// This component's owner
};

Vector2D GetVel(GameObjectInstance *pInst) {

	return pInst->mpComponent_Physics->mVelocity;

}

void SetVel(GameObjectInstance *pInst, Vector2D velocity) {

	pInst->mpComponent_Physics->mVelocity = velocity;

}

void ChangeShipSpeed(GameObjectInstance *pInst, float dt, int movementType) {

	Vector2D acceleration, curVel, velDir;
	curVel = GetVel(pInst);
	Vector2DNormalize(&velDir, &curVel);
	Vector2DZero(&acceleration);
	
	if (movementType == SHIP_MOVEMENT_TYPE_ACCEL_FORWARD) {
		Vector2DScale(&acceleration, &velDir, SHIP_ACCEL_FORWARD);
	}
	else if(movementType == SHIP_MOVEMENT_TYPE_ACCEL_FORWARD) {
		Vector2DScale(&acceleration, &velDir, SHIP_ACCEL_BACKWARD);
	}
	else {
		//TODO
		return;
	}

	Vector2DScaleAdd(&curVel, &acceleration, &curVel, dt);
	Vector2DScale(&curVel, &curVel, 0.99f);
	SetVel(pInst, curVel);
}

void ChangeShipVelDir(GameObjectInstance *pInst, float dt, int movementType) {

	Matrix2D rot;
	if (movementType == SHIP_MOVEMENT_TYPE_ACCEL_FORWARD) {
		Matrix2DRotRad(&rot, SHIP_ROT_SPEED * dt);
		
	}
	else if (movementType == SHIP_MOVEMENT_TYPE_ACCEL_FORWARD) {
		Matrix2DRotRad(&rot, -SHIP_ROT_SPEED * dt);
	}
	else {
		//TODO
		return;
	}

	Vector2D curVel = GetVel(pInst);
	Matrix2DMultVec(&curVel, &rot, &curVel);
	SetVel(pInst, curVel);
}

#endif