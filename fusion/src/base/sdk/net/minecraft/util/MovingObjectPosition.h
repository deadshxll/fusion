#pragma once
#include "../../../java/IClass.h"
#include "Vec3.h"

struct CMovingObjectPosition : IClass
{
	CMovingObjectPosition();
	CMovingObjectPosition(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	CVec3 GetBlockPosition();
	bool IsTypeOfBlock();
};

