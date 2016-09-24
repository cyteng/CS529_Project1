#include "TransformComponent.h"

Vector2D GetPosition(Component_Transform* pTransformComponent) {

	return pTransformComponent->mPosition;

}

void SetPositionXY(Component_Transform* pTransformComponent, float x, float y) {

	Vector2DSet(&(pTransformComponent->mPosition), x, y);

}

void SetPosition(Component_Transform* pTransformComponent, Vector2D newPos) {

	pTransformComponent->mPosition = newPos;

}

float GetAngle(Component_Transform* pTransformComponent) {

	return pTransformComponent->mAngle;

}

void SetAngle(Component_Transform* pTransformComponent, float angel) {

	pTransformComponent->mAngle = angel;

}

float GetScaleX(Component_Transform* pTransformComponent) {

	return pTransformComponent->mScaleX;

}

float GetScaleY(Component_Transform* pTransformComponent) {

	return pTransformComponent->mScaleY;

}

void SetScaleX(Component_Transform* pTransformComponent, float newScale) {

	pTransformComponent->mScaleX = newScale;

}

void SetScaleY(Component_Transform* pTransformComponent, float newScale) {

	pTransformComponent->mScaleY = newScale;

}

void SetUniScale(Component_Transform* pTransformComponent, float newScale) {

	pTransformComponent->mScaleX = newScale;
	pTransformComponent->mScaleY = newScale;

}

void UpdateTransform(Component_Transform* pComponent) {

	Matrix2D left, right;

	Matrix2DScale(
		&right,
		GetScaleX(pComponent),
		GetScaleY(pComponent));

	Matrix2DRotRad(&left, GetAngle(pComponent));
	Matrix2DConcat(&right, &left, &right);

	Vector2D pos = GetPosition(pComponent);
	Matrix2DTranslate(&left, pos.x, pos.y);
	Matrix2DConcat(&left, &left, &right);

	pComponent->mTransform = left;

}