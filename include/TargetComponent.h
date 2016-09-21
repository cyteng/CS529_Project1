#ifndef TARGET_COMPONENT_H
#define TARGET_COMPONENT_H

#include "GameObjectInstance.h"

struct Component_Target {

	GameObjectInstance *		mpTarget;		// Target, used by the homing missile
	GameObjectInstance *		mpOwner;		// This component's owner

};

#endif
