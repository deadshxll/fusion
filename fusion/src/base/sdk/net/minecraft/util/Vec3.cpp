#include "Vec3.h"

#include "../../../../java/java.h"
#include "../../../../util/logger.h"
#include "../../../strayCache.h"

CVec3::CVec3()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::movingObjectPosition_class;
}

CVec3::CVec3(jobject instance) : CVec3()
{
	this->Instance = instance;
}

jclass CVec3::GetClass()
{
	return this->Class;
}

jobject CVec3::GetInstance()
{
	return this->Instance;
}

Vector3 CVec3::GetNativeVector3()
{
	// ERROR AFTER THIS LINE
	float x = (float)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::vec3_xCoord);
	float y = (float)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::vec3_yCoord);
	float z = (float)Java::Env->GetDoubleField(this->GetInstance(), StrayCache::vec3_zCoord);
	return Vector3{
		x,y,z
	};
}