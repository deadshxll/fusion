#include "MovingObjectPosition.h"

#include "../../../../java/java.h"
#include "../../../strayCache.h"

CMovingObjectPosition::CMovingObjectPosition()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::movingObjectPosition_class;
}

CMovingObjectPosition::CMovingObjectPosition(jobject instance) : CMovingObjectPosition()
{
	this->Instance = instance;
}

jclass CMovingObjectPosition::GetClass()
{
	return this->Class;
}

jobject CMovingObjectPosition::GetInstance()
{
	return this->Instance;
}

CVec3 CMovingObjectPosition::GetBlockPosition()
{
	return CVec3(Java::Env->GetObjectField(this->GetInstance(), StrayCache::movingObjectPosition_hitVec));
}