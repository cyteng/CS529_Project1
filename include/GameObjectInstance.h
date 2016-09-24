#ifndef GAME_OBJECT_INSTANCE_H
#define GAME_OBJECT_INSTANCE_H

#include "GameObject.h"

#define SHIP_ACCEL_FORWARD			50.0f				// Ship forward acceleration (in m/s^2)
#define SHIP_ACCEL_BACKWARD			-100.0f				// Ship backward acceleration (in m/s^2)
#define SHIP_ROT_SPEED				(2.0f * PI)			// Ship rotation speed (radian/second)

#define SHIP_BULLET_SIZE_X		    6.0f	   
#define SHIP_BULLET_SIZE_Y		    2.0f	    

#define BULLET_SPEED				100.0f				// Bullet speed (m/s)

enum SHIP_MOVEMENT_TYPE
{
	// list of game object types
	SHIP_MOVEMENT_TYPE_ACCEL_FORWARD = 0,
	SHIP_MOVEMENT_TYPE_ACCEL_BACKWARD,
	SHIP_MOVEMENT_TYPE_ROT_LEFT,
	SHIP_MOVEMENT_TYPE_ROT_RIGHT,

	SHIP_MOVEMENT_NUM,
};

void InitializeShipBullet(GameObjectInstance *pBullet, GameObjectInstance *pShip);

void ChangeShipSpeed(GameObjectInstance *pInst, float dt, int movementType);

void ChangeShipVelDir(GameObjectInstance *pInst, float dt, int movementType);

void UpdateGameObjectTransform(GameObjectInstance* pInst);

void UpdateGameObjectPosition(GameObjectInstance* pInst, float dt);

#endif
