/*-------------------------------------------------------
Copyright (C) 2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector2D.c
Purpose: Simple 2D vector functions implementation
Language: C/C++ with Microsoft (R) C/C++ Optimizing Compiler 2015
Platform:
	-Compiler Version: 19.00.24210 for x64
	-OS: Windows 7
Project: CS529_chiyenteng_1
Author:
	-Name: Chi-Yen Teng
	-Login: chiyen.teng
	-ID: 60000416
Creation date: 09/14/16
--------------------------------------------------------*/

#include "Vector2D.h"

#define EPSILON 0.0001
#define PI      3.1415926535897932384626433832795

inline float degToRad(float degree) {
	return PI / 180.0f * degree;
}

// ---------------------------------------------------------------------------

void Vector2DZero(Vector2D *pResult) {
	Vector2DSet(pResult, 0.0f, 0.0f);
}

// ---------------------------------------------------------------------------

void Vector2DSet(Vector2D *pResult, float x, float y) {
	(*pResult).x = x;
	(*pResult).y = y;
}

// ---------------------------------------------------------------------------

void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0) {
	Vector2DScale(pResult, pVec0, -1.0f);
}

// ---------------------------------------------------------------------------

void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1) {
	float sumX = (*pVec0).x + (*pVec1).x;
	float sumY = (*pVec0).y + (*pVec1).y;
	Vector2DSet(pResult, sumX, sumY);
}

// ---------------------------------------------------------------------------

void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1) {
	float diffX = (*pVec0).x - (*pVec1).x;
	float diffY = (*pVec0).y - (*pVec1).y;
	Vector2DSet(pResult, diffX, diffY);
}

// ---------------------------------------------------------------------------

void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0) {
	float length = Vector2DLength(pVec0);
	//handle length == 0
	if (fabs(length) < EPSILON) {
		Vector2DSet(pResult, 0.f, 0.f);
	}
	else {
		Vector2DSet(pResult, (*pVec0).x / length, (*pVec0).y / length);
	}	
}

// ---------------------------------------------------------------------------

void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c) {
	Vector2DSet(pResult, (*pVec0).x * c, (*pVec0).y * c);
}

// ---------------------------------------------------------------------------

void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c) {
	Vector2DScale(pResult, pVec0, c);
	Vector2DAdd(pResult, pResult, pVec1);
}

// ---------------------------------------------------------------------------

void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c) {
	Vector2DScale(pResult, pVec0, c);
	Vector2DSub(pResult, pResult, pVec1);
}

// ---------------------------------------------------------------------------

float Vector2DLength(Vector2D *pVec0) {
	return sqrt(Vector2DSquareLength(pVec0));
}

// ---------------------------------------------------------------------------

float Vector2DSquareLength(Vector2D *pVec0) {
	float x = (*pVec0).x;
	float y = (*pVec0).y;

	return  x * x +  y * y;
}

// ---------------------------------------------------------------------------

float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1) {
	return sqrt(Vector2DSquareDistance(pVec0, pVec1));
}

// ---------------------------------------------------------------------------

float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1) {	
	float diffX = (*pVec0).x - (*pVec1).x;
	float diffY = (*pVec0).y - (*pVec1).y;

	return diffX * diffX + diffY * diffY;
}

// ---------------------------------------------------------------------------

float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1) {	
	float x0 = (*pVec0).x;
	float y0 = (*pVec0).y;
	float x1 = (*pVec1).x;
	float y1 = (*pVec1).y;

	return x0 * x1 + y0 * y1;
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleDeg(Vector2D *pResult, float angle) {
	float rad = degToRad(angle);
	Vector2DSet(pResult, cosf(rad), sinf(rad));
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleRad(Vector2D *pResult, float angle) {
	Vector2DSet(pResult, cosf(angle), sinf(angle));
}

// ---------------------------------------------------------------------------
