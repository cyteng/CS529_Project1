#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "GameObject.h"

Vector2D GetPosition(Component_Transform* pTransformComponent);

void SetPositionXY(Component_Transform* pTransformComponent, float x, float y);

void SetPosition(Component_Transform* pTransformComponent, Vector2D newPos);

float GetAngle(Component_Transform* pTransformComponent);

void SetAngle(Component_Transform* pTransformComponent, float angel);

float GetScaleX(Component_Transform* pTransformComponent);

float GetScaleY(Component_Transform* pTransformComponent);

void SetScaleX(Component_Transform* pTransformComponent, float newScale);

void SetScaleY(Component_Transform* pTransformComponent, float newScale);

void SetUniScale(Component_Transform* pTransformComponent, float newScale);

void UpdateTransform(Component_Transform* pTransformComponent);

#endif