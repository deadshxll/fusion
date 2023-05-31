#include "EntityLivingBase.h"

#include "../../../../java/java.h"
#include "../../../strayCache.h"

CEntityLivingBase::CEntityLivingBase()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::entityLivingBase_class;
}

jclass CEntityLivingBase::GetClass()
{
	return this->Class;
}

jobject CEntityLivingBase::GetInstance()
{
	return this->Instance;
}

float CEntityLivingBase::GetHealth()
{
	return Java::Env->CallFloatMethod(this->GetInstance(), StrayCache::entityLivingBase_getHealth);
}

float CEntityLivingBase::GetMaxHealth()
{
	return Java::Env->CallFloatMethod(this->GetInstance(), StrayCache::entityLivingBase_getMaxHealth);
}

bool CEntityLivingBase::CanEntityBeSeen(jobject entity) 
{
	return Java::Env->CallBooleanMethod(this->GetInstance(), StrayCache::entityLivingBase_canEntityBeSeen, entity);
}