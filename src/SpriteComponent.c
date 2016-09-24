#include "SpriteComponent.h"

unsigned long GetGameObjectType(Component_Sprite* pSpriteComponent) {

	return pSpriteComponent->mpShape->mType;

}