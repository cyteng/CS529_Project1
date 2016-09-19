/*-------------------------------------------------------
Copyright (C) 2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Math2D.c
Purpose: Simple 2D collision detection functions implementation
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

#include "Math2D.h"
#include "stdio.h"

/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{	
	if (Vector2DSquareDistance(pP, pCenter) > Radius * Radius)
		return 0;
	return 1;
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	float left = (*pRect).x - Width * 0.5f;
	float right = left + Width;
	float bottom = (*pRect).y - Height * 0.5f;
	float top = bottom + Height;

	float posX = (*pPos).x;
	float posY = (*pPos).y;

	if (posX < left || posX > right || posY < bottom || posY > top)
		return 0;

	return 1;
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{
	float rSum = Radius0 + Radius1;
	if (Vector2DSquareDistance(pCenter0, pCenter1) > rSum * rSum)
		return 0;
	return 1;
}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{
	float left0 = (*pRect0).x - Width0 * 0.5f;
	float right0 = left0 + Width0;
	float bottom0 = (*pRect0).y - Height0 * 0.5f;
	float top0 = bottom0 + Height0;

	float left1 = (*pRect1).x - Width1 * 0.5f;
	float right1 = left1 + Width1;
	float bottom1 = (*pRect1).y - Height1 * 0.5f;
	float top1 = bottom1 + Height1;

	if (right0 < left1 || left0 > right1 || top0 < bottom1 || bottom0 > top1)
		return 0;

	return 1;
}
