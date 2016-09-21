#ifndef GAME_OBJECT_INSTANCE_H
#define GAME_OBJECT_INSTANCE_H

//#include "SpriteComponent.h"
//#include "TransformComponent.h"
//#include "PhysicsComponent.h"
//#include "TargetComponent.h"

typedef struct Component_Sprite Component_Sprite;
typedef struct Component_Transform Component_Transform;
typedef struct Component_Physics Component_Physics;
typedef struct Component_Target Component_Target;

typedef struct GameObjectInstance GameObjectInstance;			// Forward declaration needed, since components need to point to their owner "GameObjectInstance"

//Game object instance structure
struct GameObjectInstance
{
	unsigned long				mFlag;						// Bit mFlag, used to indicate if the object instance is active or not

	Component_Sprite			*mpComponent_Sprite;		// Sprite component
	Component_Transform			*mpComponent_Transform;		// Transform component
	Component_Physics			*mpComponent_Physics;		// Physics component
	Component_Target			*mpComponent_Target;		// Target component, used by the homing missile
};



#endif
