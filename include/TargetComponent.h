#ifndef TARGET_COMPONENT_H
#define TARGET_COMPONENT_H

#include "GameObject.h"

GameObjectInstance *GetTarget(Component_Target* pComponent);

void SetTarget(Component_Target* pComponent, GameObjectInstance * pInst);

#endif
