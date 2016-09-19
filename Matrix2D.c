/*-------------------------------------------------------
Copyright (C) 2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Matrix2D.c
Purpose: Simple 2D matrix functions implementation
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

#include <xmmintrin.h>
#include "Matrix2D.h"

#define PI      3.1415926535897932384626433832795
#define USE_SIMD

#ifdef USE_SIMD

#define SHUFFLE_PARAM(x, y, z, w) \
((x) | ((y) << 2) | ((z) << 4) | ((w) << 6))

#define _mm_replicate_z_ps(v) \
_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(2, 2, 2, 2))

#define _mm_replicate_y_ps(v) \
_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(1, 1, 1, 1))

#define _mm_replicate_x_ps(v) \
_mm_shuffle_ps((v), (v), SHUFFLE_PARAM(0, 0, 0, 0))

#define _mm_madd_ps(a, b, c) \
_mm_add_ps(_mm_mul_ps((a), (b)), (c))

#endif

inline float degToRad(float const degree) {
	return PI / 180.0f * degree;
}

/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult) {
	for(int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			(*pResult).m[i][j] = 0.0f;
			if (i == j) {
				(*pResult).m[i][j] = 1.0f;
			}
		}
	}
}

// ---------------------------------------------------------------------------

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx) {
	for (int i = 0; i < 3; i++) {
		(*pResult).m[i][i] = (*pMtx).m[i][i];
		for (int j = i + 1; j < 3; j++) {
			float tmp = (*pMtx).m[i][j];
			(*pResult).m[i][j] = (*pMtx).m[j][i];
			(*pResult).m[j][i] = tmp;
		}
	}
}

// ---------------------------------------------------------------------------

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/

#ifdef USE_SIMD
void Matrix2DFastConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1) {
	__m128 m0row[3];
	__m128 m1row[3];
	for (int i = 0; i < 3; i++) {
		m0row[i] = _mm_set_ps(0.0f, (*pMtx0).m[i][2], (*pMtx0).m[i][1], (*pMtx0).m[i][0]);
		m1row[i] = _mm_set_ps(0.0f, (*pMtx1).m[i][2], (*pMtx1).m[i][1], (*pMtx1).m[i][0]);
	}

	for (int i = 0; i < 3; i++) {
		__m128 result;
		result = _mm_mul_ps(_mm_replicate_x_ps(m0row[i]), m1row[0]);
		result = _mm_madd_ps(_mm_replicate_y_ps(m0row[i]), m1row[1], result);
		result = _mm_madd_ps(_mm_replicate_z_ps(m0row[i]), m1row[2], result);
		(*pResult).m[i][0] = result.m128_f32[0];
		(*pResult).m[i][1] = result.m128_f32[1];
		(*pResult).m[i][2] = result.m128_f32[2];
	}
}
#else
void Matrix2DNormalConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1) {
	float m[3][3] = { 0 };
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				m[i][j] += (*pMtx0).m[i][k] * (*pMtx1).m[k][j];
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			(*pResult).m[i][j] = m[i][j];
		}
	}
}
#endif

void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1) {
#ifdef USE_SIMD
	Matrix2DFastConcat(pResult, pMtx0, pMtx1);
#else
	Matrix2DNormalConcat(pResult, pMtx0, pMtx1);
#endif	
}


// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x & y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y) {
	Matrix2DIdentity(pResult);
	(*pResult).m[0][2] = x;
	(*pResult).m[1][2] = y;
}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y) {
	Matrix2DIdentity(pResult);
	(*pResult).m[0][0] = x;
	(*pResult).m[1][1] = y;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{
	float rad = degToRad(Angle);
	Matrix2DRotRad(pResult, rad);
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{
	Matrix2DIdentity(pResult);
	(*pResult).m[0][0] = (*pResult).m[1][1] = cosf(Angle);
	(*pResult).m[0][1] = -((*pResult).m[1][0] = sinf(Angle));
}

// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/

#ifdef USE_SIMD
void Matrix2DFastMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec) {
	__m128 v = _mm_set_ps(0.0f, 1.0f, (*pVec).y, (*pVec).x);
	__m128 mCol[3];
	for (int i = 0; i < 3; i++) {
		mCol[i] = _mm_set_ps(0.0f, (*pMtx).m[2][i], (*pMtx).m[1][i], (*pMtx).m[0][i]);
	}

	__m128 result;
	result = _mm_mul_ps(_mm_replicate_x_ps(v), mCol[0]);
	result = _mm_madd_ps(_mm_replicate_y_ps(v), mCol[1], result);
	result = _mm_madd_ps(_mm_replicate_z_ps(v), mCol[2], result);
	(*pResult).x = result.m128_f32[0];
	(*pResult).y = result.m128_f32[1];
}
#else
void Matrix2DNormalMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec) {
	float x = (*pVec).x * (*pMtx).m[0][0] + (*pVec).y * (*pMtx).m[0][1] + (*pMtx).m[0][2];
	float y = (*pVec).x * (*pMtx).m[1][0] + (*pVec).y * (*pMtx).m[1][1] + (*pMtx).m[1][2];

	(*pResult).x = x;
	(*pResult).y = y;
}
#endif

void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec) {
#ifdef USE_SIMD
	Matrix2DFastMultVec(pResult, pMtx, pVec);
#else
	Matrix2DNormalMultVec(pResult, pMtx, pVec);
#endif	
}

// ---------------------------------------------------------------------------
