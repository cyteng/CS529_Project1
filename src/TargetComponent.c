#include "TargetComponent.h"

GameObjectInstance *GetTarget(Component_Target* pComponent) {

	return pComponent->mpTarget;

}

void SetTarget(Component_Target* pComponent, GameObjectInstance * pInst) {

	pComponent->mpTarget = pInst;

}