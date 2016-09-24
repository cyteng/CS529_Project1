#include "PhysicsComponent.h"

Vector2D GetVel(Component_Physics *pComponent) {

	return pComponent->mVelocity;

}

void SetVel(Component_Physics *pComponent, Vector2D velocity) {

	pComponent->mVelocity = velocity;

}

void SetVelXY(Component_Physics *pComponent, float velX, float velY) {

	pComponent->mVelocity.x = velX;
	pComponent->mVelocity.y = velY;

}

void SetVelDirAndSpeed(Component_Physics *pComponent, float angle, float speed) {

	Vector2D newVel;
	Vector2DFromAngleRad(&newVel, angle);
	Vector2DScale(&newVel, &newVel, speed);
	pComponent->mVelocity = newVel;

}

void UpdateVel(Component_Physics *pComponent, float angle, float acceleration, float dt) {

	Vector2D accelVec;
	Vector2DFromAngleRad(&accelVec, angle);
	Vector2DScaleAdd(
		&(pComponent->mVelocity), &accelVec, &(pComponent->mVelocity), acceleration * dt);
	Vector2DScale(&(pComponent->mVelocity), &(pComponent->mVelocity), 0.99f);

}