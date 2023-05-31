#pragma once

#include "../EntityLivingBase.h"

struct CEntityPlayer : CEntityLivingBase
{
	CEntityPlayer();
	CEntityPlayer(jobject instance);

	jclass GetClass();
	jobject GetInstance();
};

