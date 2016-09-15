#include <xmmintrin.h>
#include "Matrix2D.h"

#define PI      3.1415926535897932384626433832795

inline float degToRad(float degree) {
	return PI / 180.0f * degree;
}

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
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1) {	
	__m128 m0row[3];
	__m128 m1row[3];	
	for (int i = 0; i < 3; i++) {
		m1row[i] = _mm_set_ps(0.0f, (*pMtx1).m[i][2], (*pMtx1).m[i][1], (*pMtx1).m[i][0]);
		m0row[i] = _mm_set_ps(0.0f, (*pMtx0).m[i][2], (*pMtx0).m[i][1], (*pMtx0).m[i][0]);
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
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
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

// ---------------------------------------------------------------------------
