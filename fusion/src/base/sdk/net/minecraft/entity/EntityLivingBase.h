#pragma once

#include "Entity.h"

struct CEntityLivingBase : CEntity
{
	CEntityLivingBase();

	jclass GetClass();
	jobject GetInstance();

	float GetHealth();
	float GetMaxHealth();
	bool CanEntityBeSeen(jobject entity);
};

