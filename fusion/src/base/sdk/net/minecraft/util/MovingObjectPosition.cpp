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

bool CMovingObjectPosition::IsTypeOfBlock()
{
	jobject typeOfHit = Java::Env->GetObjectField(this->GetInstance(), StrayCache::movingObjectPosition_typeOfHit);
	if (!typeOfHit) return false;

	jclass movingObjectType = Java::Env->GetObjectClass(typeOfHit);
	if (!movingObjectType) return false;
	jfieldID block = Java::Env->GetStaticFieldID(movingObjectType, "BLOCK", "Lnet/minecraft/util/MovingObjectPosition$MovingObjectType;");
	if (!block) return false;
	jobject object = Java::Env->GetStaticObjectField(movingObjectType, block);
	if (!object) return false;

	return Java::Env->IsSameObject(object, typeOfHit);
}
