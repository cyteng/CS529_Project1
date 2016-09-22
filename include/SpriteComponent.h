#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "Shape.h"
#include "GameObjectInstance.h"

struct Component_Sprite
{
	Shape *mpShape;
	GameObjectInstance *	mpOwner;			// This component's owner
};

int GetGameObjectType(GameObjectInstance* pInst) {

	return (int)(pInst->mpComponent_Sprite->mpShape->mType);

}

#endif