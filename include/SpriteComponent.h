#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Shape.h"
#include "GameObjectInstance.h"

struct Component_Sprite
{
	Shape *mpShape;
	GameObjectInstance *	mpOwner;			// This component's owner
};

#endif