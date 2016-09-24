#include "GameObjectInstance.h" 
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "TargetComponent.h"

#define SHIP_ACCEL_FORWARD			50.0f				// Ship forward acceleration (in m/s^2)
#define SHIP_ACCEL_BACKWARD			-100.0f				// Ship backward acceleration (in m/s^2)
#define SHIP_ROT_SPEED				(2.0f * PI)			// Ship rotation speed (radian/second)

#define SHIP_BULLET_SIZE_X		    6.0f	   
#define SHIP_BULLET_SIZE_Y		    2.0f	    

#define BULLET_SPEED				100.0f				// Bullet speed (m/s)

void InitializeShipBullet(GameObjectInstance *pBullet, GameObjectInstance *pShip) {

	Component_Transform* pBulletTransform = pBullet->mpComponent_Transform;
	Component_Transform* pShipTransform = pShip->mpComponent_Transform;

	SetScaleX(pBullet->mpComponent_Transform, SHIP_BULLET_SIZE_X);
	SetScaleY(pBullet->mpComponent_Transform, SHIP_BULLET_SIZE_Y);

	Vector2D bulletInitPos = GetPosition(pShipTransform);

	float shipAngle = GetAngle(pShipTransform);
	SetAngle(pBulletTransform, shipAngle);

	Vector2D bulletDir;
	Vector2DFromAngleRad(&bulletDir, shipAngle);

	float shipScaleX = GetScaleX(pShipTransform);
	Vector2DScaleAdd(
		&(pBulletTransform->mPosition), &bulletDir, &bulletInitPos, shipScaleX * 0.33f);

	SetVelDirAndSpeed(pBullet->mpComponent_Physics, shipAngle, BULLET_SPEED);
}

void ChangeShipSpeed(GameObjectInstance *pInst, float dt, int movementType) {
	if (movementType == SHIP_MOVEMENT_TYPE_ACCEL_FORWARD) {
		UpdateVel(
			pInst->mpComponent_Physics,
			GetAngle(pInst->mpComponent_Transform),
			SHIP_ACCEL_FORWARD, dt);
	}
	else if (movementType == SHIP_MOVEMENT_TYPE_ACCEL_BACKWARD) {
		UpdateVel(
			pInst->mpComponent_Physics,
			GetAngle(pInst->mpComponent_Transform),
			SHIP_ACCEL_BACKWARD, dt);
	}
	else {
		//TODO
		return;
	}
}

void ChangeShipVelDir(GameObjectInstance *pInst, float dt, int movementType) {
	float angle = GetAngle(pInst->mpComponent_Transform);

	if (movementType == SHIP_MOVEMENT_TYPE_ROT_LEFT) {
		angle += SHIP_ROT_SPEED * dt;
	}
	else if (movementType == SHIP_MOVEMENT_TYPE_ROT_RIGHT) {
		angle -= SHIP_ROT_SPEED * dt;
	}
	else {
		//TODO
		return;
	}

	SetAngle(pInst->mpComponent_Transform, angle);
}


void UpdateGameObjectTransform(GameObjectInstance* pInst) {
	UpdateTransform(pInst->mpComponent_Transform);
}

void UpdateGameObjectPosition(GameObjectInstance* pInst, float dt) {
	Vector2D curPos = GetPosition(pInst->mpComponent_Transform);
	Vector2D curVel = GetVel(pInst->mpComponent_Physics);
	Vector2DScaleAdd(&curPos, &curVel, &curPos, dt);
	SetPosition(pInst->mpComponent_Transform, curPos);
}
