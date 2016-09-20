/*-------------------------------------------------------
Copyright (C) 2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Main.c
Purpose: Simple 2D math functions testing
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Math2D.h"
#include "Matrix2D.h"

#define EPSILON 0.0001f
#define PI      3.1415926535897932384626433832795
#define TRUE 1
#define FALSE 0

//
void PrintVector(char *txt, Vector2D *pVec0)
{
	printf("%s:\t%f, %f\n", txt, pVec0->x, pVec0->y);
}

float CompareVector2D(Vector2D *pSrc, Vector2D *pDst)
{
	float d = 0.0f;

	d += fabs(pSrc->x - pDst->x);
	d += fabs(pSrc->y - pDst->y);

	return d;
};

float CompareMatrix2D(Matrix2D* pSrc, Matrix2D* pDst)
{
	long i, j;
	float d = 0.0f;

	for (j = 0; j < 3; j++)
		for (i = 0; i < 3; i++)
			d += fabs(pSrc->m[j][i] - pDst->m[j][i]);

	return d;
}

float RandFloat(float lowerBound, float upperBound) {
	return lowerBound + (float)(rand()) / (float)(RAND_MAX / (upperBound - lowerBound));
}

int TestVector2DZero() {
	int error = FALSE;
	Vector2D v1, v2, result;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	result.x = result.y = 0.0f;
	
	printf("Start Testing Vector2DZero: Zero v1(%f, %f)\n", v1.x, v1.y);
	Vector2DZero(&v1);

	if(!(CompareVector2D(&result, &v1) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DSet() {
	int error = FALSE;
	Vector2D v1, result;	

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	result.x = RandFloat(-512.f, 512.f);
	result.y = RandFloat(-512.f, 512.f);

	printf("Start Testing Vector2DSet: Set v1(%f, %f) to v1(%f, %f)\n", v1.x, v1.y, result.x, result.y);
	Vector2DSet(&v1, result.x, result.y);

	if (!(CompareVector2D(&result, &v1) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DNeg() {
	int error = FALSE;
	Vector2D v1, v2, result;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	result.x = -v1.x;
	result.y = -v1.y;

	printf("Start Testing Vector2DNeg: Neg v1(%f, %f)\n", v1.x, v1.y);
	Vector2DNeg(&v2, &v1);

	if (!(CompareVector2D(&result, &v2) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DAdd() {
	int error = FALSE;
	Vector2D v1, v2, v3, result;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	v2.x = RandFloat(-512.f, 512.f);
	v2.y = RandFloat(-512.f, 512.f);
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;

	printf("Start Testing Vector2DAdd: Add v1(%f, %f) and v2(%f, %f)\n", v1.x, v1.y, v2.x, v2.y);
	Vector2DAdd(&v3, &v1, &v2);

	if (!(CompareVector2D(&result, &v3) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DSub() {
	int error = FALSE;
	Vector2D v1, v2, v3, result;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	v2.x = RandFloat(-512.f, 512.f);
	v2.y = RandFloat(-512.f, 512.f);
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;

	printf("Start Testing Vector2DSub: Sub v1(%f, %f) and v2(%f, %f)\n", v1.x, v1.y, v2.x, v2.y);
	Vector2DSub(&v3, &v1, &v2);

	if (!(CompareVector2D(&result, &v3) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DScale() {
	int error = FALSE;
	float scale;
	Vector2D v1, v2, result;
	
	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	scale = RandFloat(-512.f, 512.f);
	result.x = v1.x * scale;
	result.y = v1.y * scale;

	printf("Start Testing Vector2DScale: Scale v1(%f, %f) with %f\n", v1.x, v1.y, scale);
	Vector2DScale(&v2, &v1, scale);

	if (!(CompareVector2D(&result, &v2) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DScaleAdd() {
	int error = FALSE;
	float scale;
	Vector2D v1, v2, v3, result;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	v2.x = RandFloat(-512.f, 512.f);
	v2.y = RandFloat(-512.f, 512.f);
	scale = RandFloat(-512.f, 512.f);
	result.x = v1.x * scale + v2.x;
	result.y = v1.y * scale + v2.y;

	printf("Start Testing Vector2DScaleAdd: Scale v1(%f, %f) with %f and add v2(%f, %f)\n",
		v1.x, v1.y, scale, v2.x, v2.y);
	Vector2DScaleAdd(&v3, &v1, &v2, scale);

	if (!(CompareVector2D(&result, &v3) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DScaleSub() {
	int error = FALSE;
	float scale;
	Vector2D v1, v2, v3, result;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	v2.x = RandFloat(-512.f, 512.f);
	v2.y = RandFloat(-512.f, 512.f);
	scale = RandFloat(-512.f, 512.f);
	result.x = v1.x * scale - v2.x;
	result.y = v1.y * scale - v2.y;
	printf("Start Testing Vector2DScaleSub: Scale v1(%f, %f) with %f and sub v2(%f, %f)\n",
		v1.x, v1.y, scale, v2.x, v2.y);
	Vector2DScaleSub(&v3, &v1, &v2, scale);

	if (!(CompareVector2D(&result, &v3) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DSquareLength() {
	int error = FALSE;
	float result;
	Vector2D v1;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	result = v1.x * v1.x + v1.y * v1.y;

	printf("Start Testing Vector2DSquareLength: v1(%f, %f)\n", v1.x, v1.y);

	if (!(fabs(Vector2DSquareLength(&v1) - result)  < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DLength() {
	int error = FALSE;
	float result;
	Vector2D v1;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	result = sqrt(v1.x * v1.x + v1.y * v1.y);

	printf("Start Testing Vector2DLength: v1(%f, %f)\n", v1.x, v1.y);

	if (!(fabs(Vector2DLength(&v1) - result)  < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DNormalize() {
	int error = FALSE;
	float length;
	Vector2D v1, result;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	length = sqrt(v1.x * v1.x + v1.y * v1.y);

	if (fabs(length) < EPSILON) {
		result.x = 0.f;
		result.y = 0.f;
	}
	else {
		result.x = v1.x / length;
		result.y = v1.y / length;
	}
	
	printf("Start Testing Vector2DNormalize: v1(%f, %f)\n", v1.x, v1.y);
	Vector2DNormalize(&v1, &v1);

	if (!(CompareVector2D(&result, &v1) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DSquareDistance() {
	int error = FALSE;
	float result, diffX, diffY;
	Vector2D v1, v2;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	v2.x = RandFloat(-512.f, 512.f);
	v2.y = RandFloat(-512.f, 512.f);
	diffX = v1.x - v2.x;
	diffY = v1.y - v2.y;
	result = diffX * diffX + diffY * diffY;

	printf("Start Testing TestVector2DSquareDistance: v1(%f, %f), v2(%f, %f)\n", 
		v1.x, v1.y, v2.x, v2.y);

	if (!(fabs(Vector2DSquareDistance(&v1, &v2) - result)  < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DDistance() {
	int error = FALSE;
	float result, diffX, diffY;
	Vector2D v1, v2;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	v2.x = RandFloat(-512.f, 512.f);
	v2.y = RandFloat(-512.f, 512.f);
	diffX = v1.x - v2.x;
	diffY = v1.y - v2.y;
	result = sqrt(diffX * diffX + diffY * diffY);

	printf("Start Testing TestVector2DDistance: v1(%f, %f), v2(%f, %f)\n",
		v1.x, v1.y, v2.x, v2.y);

	if (!(fabs(Vector2DDistance(&v1, &v2) - result)  < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DDotProduct() {
	int error = FALSE;
	float result;
	Vector2D v1, v2;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	v2.x = RandFloat(-512.f, 512.f);
	v2.y = RandFloat(-512.f, 512.f);
	result = v1.x * v2.x + v1.y * v2.y;

	printf("Start Testing TestVector2DDotProduct: v1(%f, %f), v2(%f, %f)\n",
		v1.x, v1.y, v2.x, v2.y);

	if (!(fabs(Vector2DDotProduct(&v1, &v2) - result)  < EPSILON)) {
		error = TRUE;
	}
	return error;
}
int TestVector2DFromAngleDeg() {
	int error = FALSE;
	float degree, result;
	Vector2D v1, v2;

	degree = RandFloat(-180.f, 180.f);
	
	printf("Start Testing TestVector2DFromAngleDeg: degree = %f\n", degree);

	Vector2DFromAngleDeg(&v1, degree);
	Vector2DFromAngleDeg(&v2, degree);
	if (!(fabs(Vector2DDotProduct(&v1, &v2) - 1.0f)  < EPSILON)) {
		error = TRUE;
	}
	degree += 90.f;
	Vector2DFromAngleDeg(&v2, degree);
	if (!(fabs(Vector2DDotProduct(&v1, &v2))  < EPSILON)) {
		error = TRUE;
	}
	degree += 90.f;
	Vector2DFromAngleDeg(&v2, degree);
	if (!(fabs(Vector2DDotProduct(&v1, &v2) + 1.0f)  < EPSILON)) {
		error = TRUE;
	}
	degree += 90.f;
	Vector2DFromAngleDeg(&v2, degree);
	if (!(fabs(Vector2DDotProduct(&v1, &v2))  < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestVector2DFromAngleRad() {
	int error = FALSE;
	float radian, result;
	Vector2D v1, v2;

	radian = RandFloat(-PI, PI);

	printf("Start Testing TestVector2DFromAngleRad: radian = %f\n", radian);
	Vector2DFromAngleRad(&v1, radian);
	Vector2DFromAngleRad(&v2, radian);
	if (!(fabs(Vector2DDotProduct(&v1, &v2) - 1.0f)  < EPSILON)) {
		error = TRUE;
	}
	radian += PI * 0.5f;
	Vector2DFromAngleRad(&v2, radian);
	if (!(fabs(Vector2DDotProduct(&v1, &v2))  < EPSILON)) {
		error = TRUE;
	}
	radian += PI * 0.5f;
	Vector2DFromAngleRad(&v2, radian);
	if (!(fabs(Vector2DDotProduct(&v1, &v2) + 1.0f)  < EPSILON)) {
		error = TRUE;
	}
	radian += PI * 0.5f;
	Vector2DFromAngleRad(&v2, radian);
	if (!(fabs(Vector2DDotProduct(&v1, &v2))  < EPSILON)) {
		error = TRUE;
	}

	return error;
}

int TestStaticPointToStaticCircle() {
	int error = FALSE;
	float radius, distance;
	Vector2D v1, v2;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	v2.x = RandFloat(-512.f, 512.f);
	v2.y = RandFloat(-512.f, 512.f);
	distance = Vector2DDistance(&v1, &v2);
	radius = RandFloat(0.f, distance - EPSILON);

	printf("Start Testing StaticPointToStaticCircle Non Collision: "
		"v1(%f, %f), v2(%f, %f), r = %f\n", 
		v1.x, v1.y, v2.x, v2.y, radius);
	if (StaticPointToStaticCircle(&v2, &v1, radius)) {
		error = TRUE;
	}

	radius = distance + 10.f;
	printf("Start Testing StaticPointToStaticCircle Collision: \ "
		"v1(%f, %f), v2(%f, %f), r = %f\n",
		v1.x, v1.y, v2.x, v2.y, radius);
	if (!StaticPointToStaticCircle(&v2, &v1, radius)) {
		error = TRUE;
	}

	return error;
}
int TestStaticCircleToStaticCircle() {
	int error = FALSE;
	float radius1, radius2, distance;
	Vector2D v1, v2;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	v2.x = RandFloat(-512.f, 512.f);
	v2.y = RandFloat(-512.f, 512.f);
	distance = Vector2DDistance(&v1, &v2);
	radius1 = RandFloat(0.f, distance - EPSILON);
	radius2 = distance - EPSILON - radius1;

	printf("Start Testing StaticCircleToStaticCircle Non Collision: "
		"v1(%f, %f), v2(%f, %f), r1 = %f, r2 = %f\n",
		v1.x, v1.y, v2.x, v2.y, radius1, radius2);
	if (StaticCircleToStaticCircle(&v2, radius2, &v1, radius1)) {
		error = TRUE;
	}

	radius1 = RandFloat(distance * 0.5f + 10.f, distance + EPSILON);
	radius2 = RandFloat(distance * 0.5f + 10.f, distance + EPSILON);
	printf("Start Testing StaticCircleToStaticCircle Collision: "
		"v1(%f, %f), v2(%f, %f), r1 = %f, r2 = %f\n",
		v1.x, v1.y, v2.x, v2.y, radius1, radius2);
	if (!StaticCircleToStaticCircle(&v2, radius2, &v1, radius1)) {
		error = TRUE;
	}

	return error;
}
int TestStaticPointToStaticRect() {
	int error = FALSE;
	float width, height, offsetX, offsetY;
	Vector2D v1, v2;
	
	v2.x = RandFloat(-512.f, 512.f);
	v2.y = RandFloat(-512.f, 512.f);
	width = RandFloat(0.f, 512.f);
	height = RandFloat(0.f, 512.f);
	offsetX = RandFloat(-(width * 0.5f - EPSILON), width * 0.5f - EPSILON);
	offsetY = RandFloat(-(height * 0.5f - EPSILON), height * 0.5f - EPSILON);
	v1.x = v2.x + offsetX;
	v1.y = v2.y + offsetY;

	printf("Start Testing StaticPointToStaticRect Collision: "
		"point(%f, %f), center(%f, %f), width = %f, height = %f\n",
		v1.x, v1.y, v2.x, v2.y, width, height);
	if (!StaticPointToStaticRect(&v1, &v2, width, height)) {
		error = TRUE;
	}

	v1.x += width * 0.5f;
	v1.y += height * 0.5f;
	printf("Start Testing StaticPointToStaticRect Non Collision: "
		"point(%f, %f), center(%f, %f), width = %f, height = %f\n",
		v1.x, v1.y, v2.x, v2.y, width, height);
	if (StaticPointToStaticRect(&v1, &v2, width, height)) {
		error = TRUE;
	}

	return error;
}
int TestStaticRectToStaticRect() {
	int error = FALSE;
	float width1, height1, width2, height2, diffX, diffY;
	Vector2D v1, v2;

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	v2.x = RandFloat(-512.f, 512.f);
	v2.y = RandFloat(-512.f, 512.f);

	diffX = fabs(v1.x - v2.x);
	diffY = fabs(v1.y - v2.y);

	width1 = RandFloat(0.f, diffX - EPSILON);
	width2 = RandFloat(0.f, (diffX - width1) - EPSILON);
	width1 *= 2.f;
	width2 *= 2.f;

	height1 = RandFloat(0.f, diffY - EPSILON);
	height2 = RandFloat(0.f, (diffY - height1) - EPSILON);
	height1 *= 2.f;
	height2 *= 2.f;

	printf("Start Testing StaticRectToStaticRect Non Collision: "
		"center1(%f, %f), width1 = %f, height1 = %f"
		"center2(%f, %f), width2 = %f, height2 = %f\n",
		v1, width1, height1, v2, width2, height2);
	if (StaticRectToStaticRect(&v1, width1, height1, &v2, width2, height2)) {
		error = TRUE;
	}

	v1.x = RandFloat(-512.f, 512.f);
	v1.y = RandFloat(-512.f, 512.f);
	width1 = RandFloat(0.f, 512.f);
	height1 = RandFloat(0.f, 512.f);
	width2 = RandFloat(0.f, 512.f);
	height2 = RandFloat(0.f, 512.f);
	v2.x = v1.x + RandFloat(-(width1 * 0.5f - EPSILON), width1 * 0.5f - EPSILON) 
		+ width2 * 0.5f;
	v2.y = v1.y + RandFloat(-(height1 * 0.5f - EPSILON), height1 * 0.5f - EPSILON)  
		+ height2 * 0.5f;

	printf("Start Testing StaticRectToStaticRect Collision: "
		"center1(%f, %f), width1 = %f, height1 = %f"
		"center2(%f, %f), width2 = %f, height2 = %f\n",
		v1, width1, height1, v2, width2, height2);
	if (!StaticRectToStaticRect(&v1, width1, height1, &v2, width2, height2)) {
		error = TRUE;
	}

	return error;
}

int TestMatrix2DIdentity() {
	Matrix2D id, m0;
	long i, j;
	int error = FALSE;	
	
	// create an id matrix for reference
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			id.m[j][i] = (i == j) ? 1.0f : 0.0f;

	printf("Start Testing Matrix2DIdentity: \n");
	Matrix2DIdentity(&m0);

	if (!(CompareMatrix2D(&id, &m0) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestMatrix2DTranslate() {
	Matrix2D id, m0;	
	long i, j;
	int error = FALSE;
	float x, y;

	// create an id matrix for reference
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			id.m[j][i] = (i == j) ? 1.0f : 0.0f;

	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	printf("Start Testing Matrix2DTranslate: \n");
	Matrix2DTranslate(&m0, x, y);
	m0.m[0][2] -= x;
	m0.m[1][2] -= y;

	if (!(CompareMatrix2D(&id, &m0) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestMatrix2DScale() {
	Matrix2D id, m0;
	long i, j;
	int error = FALSE;
	float x, y;

	// create an id matrix for reference
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			id.m[j][i] = (i == j) ? 1.0f : 0.0f;

	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	printf("Start Testing Matrix2DScale: \n");
	Matrix2DScale(&m0, x, y);
	m0.m[0][0] /= x;
	m0.m[1][1] /= y;

	if (!(CompareMatrix2D(&id, &m0) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestMatrix2DConcat() {
	Matrix2D id, m0, m1;
	long i, j;
	int error = FALSE;
	float x, y;

	// create an id matrix for reference
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			id.m[j][i] = (i == j) ? 1.0f : 0.0f;

	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	printf("Start Testing Matrix2DConcat1: \n");
	Matrix2DTranslate(&m0, x, y);
	Matrix2DScale(&m1, x, y);
	Matrix2DConcat(&m0, &m0, &m1);
	m0.m[0][2] -= x;
	m0.m[1][2] -= y;
	m0.m[0][0] /= x;
	m0.m[1][1] /= y;

	if (!(CompareMatrix2D(&id, &m0) < EPSILON)) {
		error = TRUE;
	}

	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	printf("Start Testing Matrix2DConcat2: \n");
	Matrix2DTranslate(&m0, x, y);
	Matrix2DScale(&m1, x, y);
	Matrix2DConcat(&m0, &m1, &m0);
	m0.m[0][2] -= x * x;
	m0.m[1][2] -= y * y;
	m0.m[0][0] /= x;
	m0.m[1][1] /= y;

	if (!(CompareMatrix2D(&id, &m0) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestMatrix2DRotRad() {
	Matrix2D id, m0, m1;
	long i, j, n;
	int error = FALSE;

	// create an id matrix for reference
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			id.m[j][i] = (i == j) ? 1.0f : 0.0f;

	
	n = (rand() % 16) + 15;
	printf("Start Testing Matrix2DRotRad: rad = %f\n", 2.0f * PI / n);
	Matrix2DIdentity(&m0);
	Matrix2DRotRad(&m1, 2.0f * PI / n);

	for (i = 0; i < n; i++)
		Matrix2DConcat(&m0, &m1, &m0);

	if (!(CompareMatrix2D(&id, &m0) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestMatrix2DRotDeg() {
	Matrix2D id, m0, m1;
	long i, j, n;
	int error = FALSE;

	// create an id matrix for reference
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			id.m[j][i] = (i == j) ? 1.0f : 0.0f;


	n = (rand() % 16) + 15;
	printf("Start Testing Matrix2DRotDeg: Deg = %f\n", 360.0f / n);
	Matrix2DIdentity(&m0);
	Matrix2DRotDeg(&m1, 360.0f / n);

	for (i = 0; i < n; i++)
		Matrix2DConcat(&m0, &m1, &m0);

	if (!(CompareMatrix2D(&id, &m0) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestMatrix2DTranspose() {
	Matrix2D id, m0, m1;
	long i, j, n;
	int error = FALSE;
	float rad;

	// create an id matrix for reference
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			id.m[j][i] = (i == j) ? 1.0f : 0.0f;

	rad = rand() / (float)(RAND_MAX) * 2.0f * PI;
	printf("Start Testing Matrix2DTranspose: Rad = %f\n", rad);
	Matrix2DRotRad(&m0, rad);
	Matrix2DTranspose(&m1, &m0);
	Matrix2DConcat(&m0, &m1, &m0);

	if (!(CompareMatrix2D(&id, &m0) < EPSILON)) {
		error = TRUE;
	}

	return error;
}
int TestMatrix2DMultVec() {
	Matrix2D id, m0;
	Vector2D u;
	long i, j, n;
	int error = FALSE;
	float x, y, rad;

	// create an id matrix for reference
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			id.m[j][i] = (i == j) ? 1.0f : 0.0f;

	n = (rand() % 16) + 15;
	rad = 2.0f * PI / n;
	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	printf("Start Testing Matrix2DMultVec1: v1(%f, %f), Rad = %f\n", x, y, rad);	
	Vector2DSet(&u, x, y);
	Matrix2DRotRad(&m0, rad);

	for (i = 0; i < n; i++)
		Matrix2DMultVec(&u, &m0, &u);

	if (!((fabs(u.x - x) + fabs(u.y - y)) < EPSILON)) {
		error = TRUE;
	}

	x = 2.0f * rand() / (float)(RAND_MAX)-1.0f;
	y = 2.0f * rand() / (float)(RAND_MAX)-1.0f;

	n = (rand() % 16) + 15;
	printf("Start Testing Matrix2DMultVec2: v1(%f, %f), n = %d\n", x, y, n);
	Vector2DSet(&u, x, y);
	Matrix2DTranslate(&m0, x, y);

	for (i = 1; i < n; i++)
		Matrix2DMultVec(&u, &m0, &u);

	if (!((fabs(u.x - x * n) + fabs(u.y - y * n)) < EPSILON)) {
		error = TRUE;
	}

	return error;
}

int main()
{
	int seed = time(NULL);
    srand(seed);

	printf("\n------Running Vector Tests------\n\n");

	//====Vector2DZero Test====
	printf("Vector2DZero: %s\n\n", TestVector2DZero() ? "Fail" : "Pass");
	//====Vector2DSet Test====	
	printf("Vector2DSet: %s\n\n", TestVector2DSet() ? "Fail" : "Pass");
	//====Vector2DNeg Test====
	printf("Vector2DNeg: %s\n\n", TestVector2DNeg() ? "Fail" : "Pass");
	//====Vector2DAdd Test====	
	printf("Vector2DAdd: %s\n\n", TestVector2DAdd() ? "Fail" : "Pass");
	//====Vector2DSub Test====	
	printf("Vector2DSub: %s\n\n", TestVector2DSub() ? "Fail" : "Pass");
	//====Vector2DNormalize Test====
	printf("Vector2DNormalize: %s\n\n", TestVector2DNormalize() ? "Fail" : "Pass");
	//====Vector2DScale Test====
	printf("Vector2DScale: %s\n\n", TestVector2DScale() ? "Fail" : "Pass");
	//====Vector2DScaleAdd Test====
	printf("Vector2DScaleAdd: %s\n\n", TestVector2DScaleAdd() ? "Fail" : "Pass");
	//====Vector2DScaleSub Test====	
	printf("Vector2DScaleSub: %s\n\n", TestVector2DScaleSub() ? "Fail" : "Pass");
	//====Vector2DSquareLength Test====	
	printf("Vector2DSquareLength: %s\n\n", TestVector2DSquareLength() ? "Fail" : "Pass");
	//====Vector2DLength Test====	
	printf("Vector2DLength: %s\n\n", TestVector2DLength() ? "Fail" : "Pass");
	//====Vector2DSquareDistance Test====
	printf("Vector2DSquareDistance: %s\n\n", TestVector2DSquareDistance() ? "Fail" : "Pass");
	//====Vector2DDistance Test====
	printf("Vector2DDistance: %s\n\n", TestVector2DDistance() ? "Fail" : "Pass");
	//====Vector2DDotProduct Test====
	printf("Vector2DDotProduct: %s\n\n", TestVector2DDotProduct() ? "Fail" : "Pass");	
	//====Vector2DFromAngleDeg Test====
	printf("Vector2DFromAngleDeg: %s\n\n", TestVector2DFromAngleDeg() ? "Fail" : "Pass");
	//====Vector2DFromAngleRad Test====
	printf("Vector2DFromAngleRad: %s\n\n", TestVector2DFromAngleRad() ? "Fail" : "Pass");

	printf("\n------Running Collision Detection Tests------\n\n");

	//====StaticPointToStaticCircle Test====
	printf("StaticPointToStaticCircle: %s\n\n", TestStaticPointToStaticCircle() ? "Fail" : "Pass");
	//====StaticCircleToStaticCircle Test====
	printf("StaticCircleToStaticCircle: %s\n\n", TestStaticCircleToStaticCircle() ? "Fail" : "Pass");
	//====StaticPointToStaticRect Test====
	printf("StaticPointToStaticRect: %s\n\n", TestStaticPointToStaticRect() ? "Fail" : "Pass");
	//====StaticRectToStaticRect Test====
	printf("StaticRectToStaticRect: %s\n\n", TestStaticRectToStaticRect() ? "Fail" : "Pass");

	printf("\n------Running Matrix Tests------\n\n");

	//====Matrix2DIdentity Test====
	printf("Matrix2DIdentity: %s\n\n", TestMatrix2DIdentity() ? "Fail" : "Pass");
	//====Matrix2DTranslate Test====
	printf("Matrix2DScale: %s\n\n", TestMatrix2DTranslate() ? "Fail" : "Pass");
	//====Matrix2DTranslate Test====
	printf("Matrix2DScale: %s\n\n", TestMatrix2DScale() ? "Fail" : "Pass");
	//====Matrix2DConcat Test====
	printf("Matrix2DConcat1 & 2: %s\n\n", TestMatrix2DConcat() ? "Fail" : "Pass");
	//====Matrix2DRotRad Test====
	printf("Matrix2DRotRad: %s\n\n", TestMatrix2DRotRad() ? "Fail" : "Pass");
	//====Matrix2DRotDeg Test====
	printf("Matrix2DRotDeg: %s\n\n", TestMatrix2DRotDeg() ? "Fail" : "Pass");
	//====Matrix2DTranspose Test====
	printf("Matrix2DTranspose: %s\n\n", TestMatrix2DTranspose() ? "Fail" : "Pass");
	//====Matrix2DMultVec Test====
	printf("Matrix2DMultVec1 & 2: %s\n\n", TestMatrix2DMultVec() ? "Fail" : "Pass");

	return 1;
}