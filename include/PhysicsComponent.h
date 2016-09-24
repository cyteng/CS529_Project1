#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "GameObject.h"

Vector2D GetVel(Component_Physics *pComponent);

void SetVel(Component_Physics *pPhysicsComponent, Vector2D velocity);

void SetVelXY(Component_Physics *pPhysicsComponent, float velX, float velY);

void SetVelDirAndSpeed(Component_Physics *pPhysicsComponent, float angle, float speed);

void UpdateVel(Component_Physics *pPhysicsComponent, float angle, float acceleration, float dt);

#endif