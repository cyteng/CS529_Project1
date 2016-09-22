﻿// ---------------------------------------------------------------------------
// Project Name		:	Asteroid Game
// File Name		:	GameState_Play.c
// Author			:	Antoine Abi Chacra
// Creation Date	:	2008/01/31
// Purpose			:	implementation of the 'play' game state
// History			:
// - 2015/12/10		:	Implemented C style component based architecture 
// ---------------------------------------------------------------------------

#include "main.h"
#include "GameObjectInstance.h"
#include "Shape.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "TargetComponent.h"

// ---------------------------------------------------------------------------
// Defines

#define SHAPE_NUM_MAX				32					// The total number of different vertex buffer (Shape)
#define GAME_OBJ_INST_NUM_MAX		2048				// The total number of different game object instances


// Feel free to change these values in ordet to make the game more fun
#define SHIP_INITIAL_NUM			3					// Initial number of ship lives
#define SHIP_SIZE				    20.0f				// Ship size
#define SHIP_BULLET_SIZE_X		    6.0f	   
#define SHIP_BULLET_SIZE_Y		    2.0f	    
#define SHIP_MISSILE_SIZE_X		    10.0f	   
#define SHIP_MISSILE_SIZE_Y		    10.0f	    


#define HOMING_MISSILE_ROT_SPEED	(PI / 2.0f)			// Homing missile rotation speed (radian/second)
#define BULLET_SPEED				100.0f				// Bullet speed (m/s)

// ---------------------------------------------------------------------------

enum OBJECT_TYPE
{
	// list of game object types
	OBJECT_TYPE_SHIP = 0,
	OBJECT_TYPE_BULLET,
	OBJECT_TYPE_ASTEROID,
	OBJECT_TYPE_HOMING_MISSILE,

	OBJECT_TYPE_NUM
};

// ---------------------------------------------------------------------------
// object mFlag definition

#define FLAG_ACTIVE		0x00000001

// ---------------------------------------------------------------------------
// Static variables

// List of original vertex buffers
static Shape				sgShapes[SHAPE_NUM_MAX];									// Each element in this array represents a unique shape 
static unsigned long		sgShapeNum;													// The number of defined shapes

// list of object instances
static GameObjectInstance		sgGameObjectInstanceList[GAME_OBJ_INST_NUM_MAX];		// Each element in this array represents a unique game object instance
static unsigned long			sgGameObjectInstanceNum;								// The number of active game object instances

// pointer ot the ship object
static GameObjectInstance*		sgpShip;												// Pointer to the "Ship" game object instance

// number of ship available (lives 0 = game over)
static long						sgShipLives;											// The number of lives left

// the score = number of asteroid destroyed
static unsigned long			sgScore;												// Current score

// ---------------------------------------------------------------------------

// functions to create/destroy a game object instance
static GameObjectInstance*			GameObjectInstanceCreate(unsigned int ObjectType);			// From OBJECT_TYPE enum
static void							GameObjectInstanceDestroy(GameObjectInstance* pInst);

// ---------------------------------------------------------------------------

// Functions to add/remove components
static void AddComponent_Transform(GameObjectInstance *pInst, Vector2D *pPosition, float Angle, float ScaleX, float ScaleY);
static void AddComponent_Sprite(GameObjectInstance *pInst, unsigned int ShapeType);
static void AddComponent_Physics(GameObjectInstance *pInst, Vector2D *pVelocity);
static void AddComponent_Target(GameObjectInstance *pInst, GameObjectInstance *pTarget);

static void RemoveComponent_Transform(GameObjectInstance *pInst);
static void RemoveComponent_Sprite(GameObjectInstance *pInst);
static void RemoveComponent_Physics(GameObjectInstance *pInst);
static void RemoveComponent_Target(GameObjectInstance *pInst);

// ---------------------------------------------------------------------------

// "Load" function of this state
void GameStateAsteroidsLoad(void)
{
	Shape* pShape = NULL;

	// Zero the shapes array
	memset(sgShapes, 0, sizeof(Shape) * SHAPE_NUM_MAX);
	// No shapes at this point
	sgShapeNum = 0;

	// The ship object instance hasn't been created yet, so this "sgpShip" pointer is initialized to 0
	sgpShip = 0;



	/// Create the game objects(shapes) : Ships, Bullet, Asteroid and Missile
	// How to:
	// -- Remember to create normalized shapes, which means all the vertices' coordinates should be in the [-0.5;0.5] range. Use the object instances' scale values to resize the shape.
	// -- Call “AEGfxMeshStart” to inform the graphics manager that you are about the start sending triangles.
	// -- Call “AEGfxTriAdd” to add 1 triangle.
	// -- A triangle is formed by 3 counter clockwise vertices (points).
	// -- Create all the points between (-0.5, -0.5) and (0.5, 0.5), and use the object instance's scale to change the size.
	// -- Each point can have its own color.
	// -- The color format is : ARGB, where each 2 hexadecimal digits represent the value of the Alpha, Red, Green and Blue respectively. Note that alpha blending(Transparency) is not implemented.
	// -- Each point can have its own texture coordinate (set them to 0.0f in case you’re not applying a texture).
	// -- An object (Shape) can have multiple triangles.
	// -- Call “AEGfxMeshEnd” to inform the graphics manager that you are done creating a mesh, which will return a pointer to the mesh you just created.

	

	// =====================
	// Create the ship shape
	// =====================

	pShape = sgShapes + sgShapeNum++;
	pShape->mType = OBJECT_TYPE_SHIP;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f,  0.5f, 0xFFFF0000, 0.0f, 0.0f, 
		-0.5f, -0.5f, 0xFFFF0000, 0.0f, 0.0f,
		 0.5f,  0.0f, 0xFFFFFFFF, 0.0f, 0.0f); 
	pShape->mpMesh = AEGfxMeshEnd();


	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// TO DO 4:
	// -- Create the bullet shape
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////

	pShape = sgShapes + sgShapeNum++;
	pShape->mType = OBJECT_TYPE_BULLET;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	AEGfxTriAdd(		
		0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
	pShape->mpMesh = AEGfxMeshEnd();


	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// TO DO 7:
	// -- Create the asteroid shape
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////

	pShape = sgShapes + sgShapeNum++;
	pShape->mType = OBJECT_TYPE_ASTEROID;

	AEGfxMeshStart();
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFF8A4B08, 0.0f, 0.0f,
		-0.5f, -0.5f, 0xFF8A4B08, 0.0f, 0.0f,
		0.5f, 0.5f, 0xFF8A4B08, 0.0f, 0.0f);
	AEGfxTriAdd(
		0.5f, 0.5f, 0xFF8A4B08, 0.0f, 0.0f,
		-0.5f, -0.5f, 0xFF8A4B08, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFF8A4B08, 0.0f, 0.0f);
	pShape->mpMesh = AEGfxMeshEnd();

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// TO DO 10:
	// -- Create the homing missile shape
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////

	pShape = sgShapes + sgShapeNum++;
	pShape->mType = OBJECT_TYPE_HOMING_MISSILE;

	AEGfxMeshStart();
	
	AEGfxTriAdd(
		-0.5f, 0.5f, 0xFFFE642E, 0.0f, 0.0f,
		-0.5f, -0.5f, 0xFFFE642E, 0.0f, 0.0f,
		0.5f, 0.5f, 0xFFFE642E, 0.0f, 0.0f);
	AEGfxTriAdd(
		0.5f, 0.5f, 0xFFFE642E, 0.0f, 0.0f,
		0.5f, -0.5f, 0xFFFE642E, 0.0f, 0.0f,
		-0.5f, -0.5f, 0xFFFE642E, 0.0f, 0.0f
		);
	AEGfxTriAdd(
		-0.4f, 0.0f, 0xFFFE642E, 0.0f, 0.0f,
		-0.9f, -0.5f, 0xFFFE642E, 0.0f, 0.0f,
		-0.9f, 0.5f, 0xFFFE642E, 0.0f, 0.0f);

	pShape->mpMesh = AEGfxMeshEnd();
}

// ---------------------------------------------------------------------------

// "Initialize" function of this state
void GameStateAsteroidsInit(void)
{
	AEGfxSetBackgroundColor(0.0f, 0.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	// zero the game object instance array
	memset(sgGameObjectInstanceList, 0, sizeof(GameObjectInstance)* GAME_OBJ_INST_NUM_MAX);
	// No game object instances (sprites) at this point
	sgGameObjectInstanceNum = 0;

	// create the main ship
	sgpShip = GameObjectInstanceCreate(OBJECT_TYPE_SHIP);
	SetUniScale(sgpShip, SHIP_SIZE);

	/*GameObjectInstance* pTestBullet = GameObjectInstanceCreate(OBJECT_TYPE_BULLET);
	SetScaleX(pTestBullet, 10.0f);
	SetScaleY(pTestBullet, 2.0f);*/

	/*GameObjectInstance* pTestAsteroid = GameObjectInstanceCreate(OBJECT_TYPE_ASTEROID);
	SetScaleX(pTestAsteroid, 50.0f);
	SetScaleY(pTestAsteroid, 50.0f);*/

	/*GameObjectInstance* pTestHomingMissle = GameObjectInstanceCreate(OBJECT_TYPE_HOMING_MISSILE);
	SetScaleX(pTestHomingMissle, 10.0f);
	SetScaleY(pTestHomingMissle, 10.0f);*/

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// TO DO 8:
	// -- Create at least 3 asteroid instances, each with a different size, 
	//    using the "GameObjInstCreate" function
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////

	GameObjectInstance* pTestAsteroid0 = GameObjectInstanceCreate(OBJECT_TYPE_ASTEROID);
	SetScaleX(pTestAsteroid0, 50.0f);
	SetScaleY(pTestAsteroid0, 50.0f);
	SetPositionXY(pTestAsteroid0, 100.f, 200.f);
	SetVelXY(pTestAsteroid0, 20.f, -20.f);

	GameObjectInstance* pTestAsteroid1 = GameObjectInstanceCreate(OBJECT_TYPE_ASTEROID);
	SetScaleX(pTestAsteroid1, 30.0f);
	SetScaleY(pTestAsteroid1, 30.0f);
	SetPositionXY(pTestAsteroid1, 150.f, 100.f);
	SetVelXY(pTestAsteroid1, -30.f, 5.f);

	GameObjectInstance* pTestAsteroid2 = GameObjectInstanceCreate(OBJECT_TYPE_ASTEROID);
	SetScaleX(pTestAsteroid2, 40.0f);
	SetScaleY(pTestAsteroid2, 40.0f);
	SetPositionXY(pTestAsteroid2, -100.f, -100.f);
	SetVelXY(pTestAsteroid2, 10.f, 5.f);

	// reset the score and the number of ship
	sgScore			= 0;
	sgShipLives		= SHIP_INITIAL_NUM;
}

// ---------------------------------------------------------------------------

// "Update" function of this state
void GameStateAsteroidsUpdate(void)
{
	unsigned long i;
	float winMaxX, winMaxY, winMinX, winMinY;
	double frameTime;

	// ==========================================================================================
	// Getting the window's world edges (These changes whenever the camera moves or zooms in/out)
	// ==========================================================================================
	winMaxX = AEGfxGetWinMaxX();
	winMaxY = AEGfxGetWinMaxY();
	winMinX = AEGfxGetWinMinX();
	winMinY = AEGfxGetWinMinY();

	
	// ======================
	// Getting the frame time
	// ======================

	frameTime = AEFrameRateControllerGetFrameTime();

	// =========================
	// Update according to input
	// =========================

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// TO DO 3:
	// -- Compute the forward/backward acceleration of the ship when Up/Down are pressed
	// -- Use the acceleration to update the velocity of the ship
	// -- Limit the maximum velocity of the ship
	// -- IMPORTANT: The current input code moves the ship by simply adjusting its position
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	if (AEInputCheckCurr(VK_UP)) {		
		ChangeShipSpeed(sgpShip, frameTime, SHIP_MOVEMENT_TYPE_ACCEL_FORWARD);
	}

	if (AEInputCheckCurr(VK_DOWN)) {
		ChangeShipSpeed(sgpShip, frameTime, SHIP_MOVEMENT_TYPE_ACCEL_BACKWARD);
	}

	if (AEInputCheckCurr(VK_LEFT)) {
		ChangeShipVelDir(sgpShip, frameTime, SHIP_MOVEMENT_TYPE_ROT_LEFT);
	}

	if (AEInputCheckCurr(VK_RIGHT)) {
		ChangeShipVelDir(sgpShip, frameTime, SHIP_MOVEMENT_TYPE_ROT_RIGHT);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// TO DO 5:
	// -- Create a bullet instance when SPACE is triggered, using the "GameObjInstCreate" function
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	if (AEInputCheckTriggered(VK_SPACE))
	{
		GameObjectInstance* pNewBullet = GameObjectInstanceCreate(OBJECT_TYPE_BULLET);
		SetScaleX(pNewBullet, SHIP_BULLET_SIZE_X);
		SetScaleY(pNewBullet, SHIP_BULLET_SIZE_Y);
		
		Vector2D newPos = GetPosition(sgpShip);	

		float shipAngel = GetAngel(sgpShip);
		Vector2D shipDir;
		Vector2DFromAngleRad(&shipDir, shipAngel);

		float shipScaleX = GetScaleX(sgpShip);
		Vector2DScaleAdd(&newPos, &shipDir, &newPos, shipScaleX * 0.33f);

		SetPosition(pNewBullet, newPos);
		
		SetAngel(pNewBullet, shipAngel);
		
		Vector2D bulletVel;
		Vector2DScale(&bulletVel, &shipDir, BULLET_SPEED);
		SetVel(pNewBullet, bulletVel);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// TO DO 11:
	// -- Create a homing missile instance when M is triggered
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	if (AEInputCheckTriggered('M'))
	{
		GameObjectInstance* pNewHomingMissile = GameObjectInstanceCreate(OBJECT_TYPE_HOMING_MISSILE);
		SetScaleX(pNewHomingMissile, SHIP_MISSILE_SIZE_X);
		SetScaleY(pNewHomingMissile, SHIP_MISSILE_SIZE_Y);

		Vector2D newPos = GetPosition(sgpShip);

		float shipAngel = GetAngel(sgpShip);
		Vector2D shipDir;
		Vector2DFromAngleRad(&shipDir, shipAngel);

		float shipScaleX = GetScaleX(sgpShip);
		Vector2DScaleAdd(&newPos, &shipDir, &newPos, shipScaleX * 0.33f);

		SetPosition(pNewHomingMissile, newPos);

		SetAngel(pNewHomingMissile, shipAngel);

		Vector2D missileVel;
		Vector2DScale(&missileVel, &shipDir, BULLET_SPEED);
		SetVel(pNewHomingMissile, missileVel);
	}

	if (AEInputCheckTriggered('1')) {
		gGameStateNext = GS_RESTART;
	}

	if (AEInputCheckTriggered('2')) {
		gGameStateNext = GS_QUIT;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// TO DO 2:
	// Update the positions of all active game object instances
	// -- Positions are updated here (P1 = V1*t + P0)
	// -- If implemented correctly, you will be able to control the ship (basic 2D movement)
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	for (i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjectInstance* pInst = sgGameObjectInstanceList + i;

		// skip non-active object
		if ((pInst->mFlag & FLAG_ACTIVE) == 0)
			continue;

		Vector2D curVel = GetVel(pInst);
		UpdatePosition(pInst, curVel, frameTime);
		
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// TO DO 6: Specific game object behavior, according to type
	// -- Bullet: Destroy when it's outside the viewport
	// -- Asteroids: If it's outside the viewport, wrap around viewport.
	// -- Homing missile: If it's outside the viewport, wrap around viewport.
	// -- Homing missile: Follow/Acquire target
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	for (i = 0; i < GAME_OBJ_INST_NUM_MAX; i++) {
		GameObjectInstance* pInst = sgGameObjectInstanceList + i;

		// skip non-active object
		if ((pInst->mFlag & FLAG_ACTIVE) == 0)
			continue;
		
		int objectType = GetGameObjectType(pInst);

		// check if the object is a ship
		if (objectType == OBJECT_TYPE_SHIP)
		{
			// warp the ship from one end of the screen to the other
			pInst->mpComponent_Transform->mPosition.x = 
				AEWrap(pInst->mpComponent_Transform->mPosition.x, 
					winMinX - SHIP_SIZE * 0.5f, winMaxX + SHIP_SIZE * 0.5f);
			pInst->mpComponent_Transform->mPosition.y = 
				AEWrap(pInst->mpComponent_Transform->mPosition.y, 
					winMinY - SHIP_SIZE * 0.5f, winMaxY + SHIP_SIZE * 0.5f);
		}

		// Bullet behavior
		else if (objectType == OBJECT_TYPE_BULLET) {
			Vector2D origin;
			Vector2DZero(&origin);
			Vector2D bulletPos = GetPosition(pInst);

			int inside =
				StaticPointToStaticRect(
					&bulletPos, &origin,
					(winMaxX + SHIP_BULLET_SIZE_X) * 2.f, 
					(winMaxY + SHIP_BULLET_SIZE_X) * 2.f);
			
			if (!inside) {
				GameObjectInstanceDestroy(pInst);
			}
		}

		// Asteroid behavior
		else if (objectType == OBJECT_TYPE_ASTEROID) {
			pInst->mpComponent_Transform->mPosition.x =
				AEWrap(pInst->mpComponent_Transform->mPosition.x,
					winMinX - GetScaleX(pInst) * 0.5f, winMaxX + GetScaleX(pInst) * 0.5f);
			pInst->mpComponent_Transform->mPosition.y =
				AEWrap(pInst->mpComponent_Transform->mPosition.y,
					winMinY - GetScaleY(pInst) * 0.5f, winMaxY + GetScaleY(pInst) * 0.5f);
		}

		// Homing missile behavior (Not every game object instance will have this component!)
		else if (objectType == OBJECT_TYPE_HOMING_MISSILE) {
			GameObjectInstance *target = pInst->mpComponent_Target->mpTarget;
			
			if (pInst->mpComponent_Target->mpTarget == NULL || 
				(target->mFlag & FLAG_ACTIVE) == 0) {

				for (int j = 0; j < GAME_OBJ_INST_NUM_MAX; j++) {				
					GameObjectInstance* pTargetInst = sgGameObjectInstanceList + j;

					// skip non-active object
					if ((pTargetInst->mFlag & FLAG_ACTIVE) == 0 ||
						GetGameObjectType(pTargetInst) != OBJECT_TYPE_ASTEROID)
						continue;

					pInst->mpComponent_Target->mpTarget = pTargetInst;
					break;
				}
			}
			else {
				Vector2D targetPos = GetPosition(target);
				Vector2D missilePos = GetPosition(pInst);
				Vector2D missileToTarget;
				Vector2DSub(&missileToTarget, &targetPos, &missilePos);
				Vector2D missileDir;

				Vector2DFromAngleRad(&missileDir, GetAngel(pInst) + PI * 0.5f);
				if (Vector2DDotProduct(&missileToTarget, &missileDir) >= 0.f) {
					SetAngel(pInst, GetAngel(pInst) + HOMING_MISSILE_ROT_SPEED * frameTime);					
				}
				else {
					SetAngel(pInst, GetAngel(pInst) - HOMING_MISSILE_ROT_SPEED * frameTime);
				}

				Vector2D newVel;
				Vector2DFromAngleRad(&newVel, GetAngel(pInst));
				Vector2DScale(&newVel, &newVel, BULLET_SPEED);
				SetVel(pInst, newVel);
			}
			
			pInst->mpComponent_Transform->mPosition.x =
				AEWrap(pInst->mpComponent_Transform->mPosition.x,
					winMinX - SHIP_BULLET_SIZE_X * 0.5f, winMaxX + SHIP_BULLET_SIZE_X * 0.5f);
			pInst->mpComponent_Transform->mPosition.y =
				AEWrap(pInst->mpComponent_Transform->mPosition.y,
					winMinY - SHIP_BULLET_SIZE_X * 0.5f, winMaxY + SHIP_BULLET_SIZE_X * 0.5f);
		}
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// TO DO 9: Check for collision
	// Important: Take the object instance's scale values into consideration when checking for collision.
	// -- Asteroid - Bullet: Rectangle to Point check. If they collide, destroy both.
	// -- Asteroid - Ship: Rectangle to Rectangle check. If they collide, destroy the asteroid, 
	//    reset the ship position to the center of the screen.
	// -- Asteroid - Homing Missile: Rectangle to Rectangle check.
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	
	for (i = 0; i < GAME_OBJ_INST_NUM_MAX; i++) {
		GameObjectInstance* pColliderInst = sgGameObjectInstanceList + i;

		// skip non-active object
		if ((pColliderInst->mFlag & FLAG_ACTIVE) == 0)
			continue;

		int colliderObjectType = GetGameObjectType(pColliderInst);

		if (colliderObjectType == OBJECT_TYPE_ASTEROID) {
			for (int j = 0; j < GAME_OBJ_INST_NUM_MAX; j++) {
				GameObjectInstance* pTargetInst = sgGameObjectInstanceList + j;

				// skip non-active or ASTEROIDs
				if ((pTargetInst->mFlag & FLAG_ACTIVE) == 0 ||
					GetGameObjectType(pTargetInst) == OBJECT_TYPE_ASTEROID)
					continue;

				int targetObjectType = GetGameObjectType(pTargetInst);
				Vector2D targetPos = GetPosition(pTargetInst);
				Vector2D colliderPos = GetPosition(pColliderInst);
				float colliderWidth = GetScaleX(pColliderInst);
				float colliderHeight = GetScaleY(pColliderInst);

				int collision;

				//asteriod vs ship
				if (targetObjectType == OBJECT_TYPE_SHIP) {					 
					collision = 
						StaticRectToStaticRect(
							&colliderPos, colliderWidth, colliderHeight,
							&targetPos, GetScaleX(pTargetInst), GetScaleY(pTargetInst));
					
					//Game Over
					if (collision) {
						pTargetInst->mFlag &= ~FLAG_ACTIVE;
						GameObjectInstanceDestroy(pTargetInst);
					}
				}
				//asteriod vs bullet
				else if (targetObjectType == OBJECT_TYPE_BULLET) {
					collision =
						StaticPointToStaticRect(
							&targetPos, &colliderPos, colliderWidth, colliderHeight);
					if (collision) {
						pColliderInst->mFlag &= ~FLAG_ACTIVE;
						GameObjectInstanceDestroy(pColliderInst);
						pTargetInst->mFlag &= ~FLAG_ACTIVE;
						GameObjectInstanceDestroy(pTargetInst);
					}
				}
				//asteriod vs missile
				else if (targetObjectType == OBJECT_TYPE_HOMING_MISSILE) {
					collision =
						StaticRectToStaticRect(
							&colliderPos, colliderWidth, colliderHeight,
							&targetPos, GetScaleX(pTargetInst), GetScaleY(pTargetInst));
					if (collision) {
						pColliderInst->mFlag &= ~FLAG_ACTIVE;
						GameObjectInstanceDestroy(pColliderInst);
						pTargetInst->mFlag &= ~FLAG_ACTIVE;
						GameObjectInstanceDestroy(pTargetInst);
					}
				}

			}
		}

	}
	
	// =====================================
	// calculate the matrix for all objects
	// =====================================

	for (i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjectInstance* pInst = sgGameObjectInstanceList + i;
		
		// skip non-active object
		if ((pInst->mFlag & FLAG_ACTIVE) == 0)
			continue;


		/////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////
		// TO DO 1:
		// -- Build the transformation matrix of each active game object instance
		// -- After you implement this step, you should see the player's ship
		// -- Reminder: Scale should be applied first, then rotation, then translation.	
		/////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////

		// Compute the scaling matrix
		// Compute the rotation matrix 
		// Compute the translation matrix
		// Concatenate the 3 matrix in the correct order in the object instance's transform component's "mTransform" matrix

		UpdateTransform(pInst);

	}
}

// ---------------------------------------------------------------------------

void GameStateAsteroidsDraw(void)
{
	unsigned long i;
	double frameTime;


	AEGfxSetRenderMode(AE_GFX_RM_COLOR);
	AEGfxTextureSet(NULL, 0, 0);
	AEGfxSetTintColor(1.0f, 1.0f, 1.0f, 1.0f);

	// draw all object instances in the list

	for (i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjectInstance* pInst = sgGameObjectInstanceList + i;

		// skip non-active object
		if ((pInst->mFlag & FLAG_ACTIVE) == 0)
			continue;
		
		// Already implemented. Explanation:
		// Step 1 & 2 are done outside the for loop (AEGfxSetRenderMode, AEGfxTextureSet, AEGfxSetTintColor) since all our objects share the same material.
		// If you want to have objects with difference materials (Some with textures, some without, some with transparency etc...)
		// then you'll need to move those functions calls inside the for loop
		// 1 - Set Render Mode (Color or texture)
		// 2 - Set all needed parameters (Color blend, textures, etc..)
		// 3 - Set the current object instance's mTransform matrix using "AEGfxSetTransform"
		// 4 - Draw the shape used by the current object instance using "AEGfxMeshDraw"

		AEGfxSetTransform(pInst->mpComponent_Transform->mTransform.m);
		AEGfxMeshDraw(pInst->mpComponent_Sprite->mpShape->mpMesh, AE_GFX_MDM_TRIANGLES);
	}
}

// ---------------------------------------------------------------------------

void GameStateAsteroidsFree(void)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// TO DO 12:
	//  -- Destroy all the active game object instances, using the “GameObjInstanceDestroy” function.
	//  -- Reset the number of active game objects instances
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	
	sgGameObjectInstanceNum = 0;

	for (int i = 0; i < GAME_OBJ_INST_NUM_MAX; i++) {
		GameObjectInstance* pInst = sgGameObjectInstanceList + i;

		pInst->mFlag &= ~FLAG_ACTIVE;
		GameObjectInstanceDestroy(pInst);
	}

}

// ---------------------------------------------------------------------------

void GameStateAsteroidsUnload(void)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// TO DO 13:
	//  -- Destroy all the shapes, using the “AEGfxMeshFree” function.
	/////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////	
	Shape* pShape;
	while (sgShapeNum > 0) {
		pShape = sgShapes + --sgShapeNum;
		AEGfxMeshFree(pShape->mpMesh);
	}
}

// ---------------------------------------------------------------------------

GameObjectInstance* GameObjectInstanceCreate(unsigned int ObjectType)			// From OBJECT_TYPE enum)
{
	unsigned long i;
	
	// loop through the object instance list to find a non-used object instance
	for (i = 0; i < GAME_OBJ_INST_NUM_MAX; i++)
	{
		GameObjectInstance* pInst = sgGameObjectInstanceList + i;

		// Check if current instance is not used
		if (pInst->mFlag == 0)
		{
			// It is not used => use it to create the new instance

			// Active the game object instance
			pInst->mFlag = FLAG_ACTIVE;

			pInst->mpComponent_Transform = 0;
			pInst->mpComponent_Sprite = 0;
			pInst->mpComponent_Physics = 0;
			pInst->mpComponent_Target = 0;

			// Add the components, based on the object type
			switch (ObjectType)
			{
			case OBJECT_TYPE_SHIP:
				AddComponent_Sprite(pInst, OBJECT_TYPE_SHIP);
				AddComponent_Transform(pInst, 0, 0.0f, 1.0f, 1.0f);
				AddComponent_Physics(pInst, 0);
				break;

			case OBJECT_TYPE_BULLET:
				AddComponent_Sprite(pInst, OBJECT_TYPE_BULLET);
				AddComponent_Transform(pInst, 0, 0.0f, 1.0f, 1.0f);
				AddComponent_Physics(pInst, 0);
				break;

			case OBJECT_TYPE_ASTEROID:
				AddComponent_Sprite(pInst, OBJECT_TYPE_ASTEROID);
				AddComponent_Transform(pInst, 0, 0.0f, 1.0f, 1.0f);
				AddComponent_Physics(pInst, 0);
				break;

			case OBJECT_TYPE_HOMING_MISSILE:
				AddComponent_Sprite(pInst, OBJECT_TYPE_HOMING_MISSILE);
				AddComponent_Transform(pInst, 0, 0.0f, 1.0f, 1.0f);
				AddComponent_Physics(pInst, 0);
				AddComponent_Target(pInst, 0);
				break;
			}

			++sgGameObjectInstanceNum;

			// return the newly created instance
			return pInst;
		}
	}

	// Cannot find empty slot => return 0
	return 0;
}

// ---------------------------------------------------------------------------

void GameObjectInstanceDestroy(GameObjectInstance* pInst)
{
	// if instance is destroyed before, just return
	if (pInst->mFlag == 0)
		return;

	// Zero out the mFlag
	pInst->mFlag = 0;

	RemoveComponent_Transform(pInst);
	RemoveComponent_Sprite(pInst);
	RemoveComponent_Physics(pInst);
	RemoveComponent_Target(pInst);

	--sgGameObjectInstanceNum;
}

// ---------------------------------------------------------------------------

void AddComponent_Transform(GameObjectInstance *pInst, Vector2D *pPosition, float Angle, float ScaleX, float ScaleY)
{
	if (0 != pInst)
	{
		if (0 == pInst->mpComponent_Transform)
		{
			pInst->mpComponent_Transform = (Component_Transform *)calloc(1, sizeof(Component_Transform));
		}

		Vector2D zeroVec2;
		AEVec2Zero(&zeroVec2);

		pInst->mpComponent_Transform->mScaleX = ScaleX;
		pInst->mpComponent_Transform->mScaleY = ScaleY;
		pInst->mpComponent_Transform->mPosition = pPosition ? *pPosition : zeroVec2;;
		pInst->mpComponent_Transform->mAngle = Angle;
		pInst->mpComponent_Transform->mpOwner = pInst;
	}
}

// ---------------------------------------------------------------------------

void AddComponent_Sprite(GameObjectInstance *pInst, unsigned int ShapeType)
{
	if (0 != pInst)
	{
		if (0 == pInst->mpComponent_Sprite)
		{
			pInst->mpComponent_Sprite = (Component_Sprite *)calloc(1, sizeof(Component_Sprite));
		}
	
		pInst->mpComponent_Sprite->mpShape = sgShapes + ShapeType;
		pInst->mpComponent_Sprite->mpOwner = pInst;
	}
}

// ---------------------------------------------------------------------------

void AddComponent_Physics(GameObjectInstance *pInst, Vector2D *pVelocity)
{
	if (0 != pInst)
	{
		if (0 == pInst->mpComponent_Physics)
		{
			pInst->mpComponent_Physics = (Component_Physics *)calloc(1, sizeof(Component_Physics));
		}

		Vector2D zeroVec2;
		Vector2DZero(&zeroVec2);

		pInst->mpComponent_Physics->mVelocity = pVelocity ? *pVelocity : zeroVec2;
		pInst->mpComponent_Physics->mpOwner = pInst;
	}
}

// ---------------------------------------------------------------------------

void AddComponent_Target(GameObjectInstance *pInst, GameObjectInstance *pTarget)
{
	if (0 != pInst)
	{
		if (0 == pInst->mpComponent_Target)
		{
			pInst->mpComponent_Target = (Component_Target *)calloc(1, sizeof(Component_Target));
		}

		pInst->mpComponent_Target->mpTarget = pTarget;
		pInst->mpComponent_Target->mpOwner = pInst;
	}
}

// ---------------------------------------------------------------------------

void RemoveComponent_Transform(GameObjectInstance *pInst)
{
	if (0 != pInst)
	{
		if (0 != pInst->mpComponent_Transform)
		{
			free(pInst->mpComponent_Transform);
			pInst->mpComponent_Transform = 0;
		}
	}
}

// ---------------------------------------------------------------------------

void RemoveComponent_Sprite(GameObjectInstance *pInst)
{
	if (0 != pInst)
	{
		if (0 != pInst->mpComponent_Sprite)
		{
			free(pInst->mpComponent_Sprite);
			pInst->mpComponent_Sprite = 0;
		}
	}
}

// ---------------------------------------------------------------------------

void RemoveComponent_Physics(GameObjectInstance *pInst)
{
	if (0 != pInst)
	{
		if (0 != pInst->mpComponent_Physics)
		{
			free(pInst->mpComponent_Physics);
			pInst->mpComponent_Physics = 0;
		}
	}
}

// ---------------------------------------------------------------------------

void RemoveComponent_Target(GameObjectInstance *pInst)
{
	if (0 != pInst)
	{
		if (0 != pInst->mpComponent_Target)
		{
			free(pInst->mpComponent_Target);
			pInst->mpComponent_Target = 0;
		}
	}
}
