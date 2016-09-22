#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Vector2D.h"
#include "Matrix2D.h"
#include "GameObjectInstance.h"

struct Component_Transform {
	
	Vector2D					mPosition;			// Current position
	float					mAngle;				// Current angle
	float					mScaleX;			// Current X scaling value
	float					mScaleY;			// Current Y scaling value

	Matrix2D					mTransform;			// Object transformation matrix: Each frame, calculate the object instance's transformation matrix and save it here

	GameObjectInstance *	mpOwner;			// This component's owner

};

Vector2D GetPosition(GameObjectInstance* pInst) {

	return pInst->mpComponent_Transform->mPosition;

}

void SetPositionXY(GameObjectInstance* pInst, float x, float y) {

	Vector2DSet(&(pInst->mpComponent_Transform->mPosition), x, y);

}

void SetPosition(GameObjectInstance* pInst, Vector2D newPos) {

	pInst->mpComponent_Transform->mPosition = newPos;

}

float GetAngel(GameObjectInstance* pInst) {

	return pInst->mpComponent_Transform->mAngle;

}

void SetAngel(GameObjectInstance* pInst, float angel) {

	pInst->mpComponent_Transform->mAngle = angel;

}

float GetScaleX(GameObjectInstance* pInst) {

	return pInst->mpComponent_Transform->mScaleX;

}

float GetScaleY(GameObjectInstance* pInst) {

	return pInst->mpComponent_Transform->mScaleY;

}

float SetScaleX(GameObjectInstance* pInst, float newScale) {

	pInst->mpComponent_Transform->mScaleX = newScale;

}

float SetScaleY(GameObjectInstance* pInst, float newScale) {

	pInst->mpComponent_Transform->mScaleY = newScale;

}

float SetUniScale(GameObjectInstance* pInst, float newScale) {

	pInst->mpComponent_Transform->mScaleX = newScale;
	pInst->mpComponent_Transform->mScaleY = newScale;

}

void UpdateTransform(GameObjectInstance* pInst) {

	Matrix2D left, right;

	Matrix2DScale(&right, GetScaleX(pInst), GetScaleY(pInst));
	
	Matrix2DRotRad(&left, GetAngel(pInst));
	Matrix2DConcat(&right, &left, &right);

	Vector2D pos = GetPosition(pInst);
	Matrix2DTranslate(&left, pos.x, pos.y);
	Matrix2DConcat(&left, &left, &right);

	pInst->mpComponent_Transform->mTransform = left;

}

void UpdatePosition(GameObjectInstance* pInst, Vector2D vel, float dt) {

	Vector2D curPos = GetPosition(pInst);
	Vector2DScaleAdd(&curPos, &vel, &curPos, dt);
	SetPosition(pInst, curPos);

}

#endif