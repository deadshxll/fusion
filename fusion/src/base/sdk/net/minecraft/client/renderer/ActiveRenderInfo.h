#pragma once

#include "../../../../java/IClass.h"
#include "../../../../../util/math/geometry.h"


struct CActiveRenderInfo : IClass
{
	CActiveRenderInfo();

	jclass GetClass();
	jobject GetInstance();

	Matrix ProjectionMatrix();
	Matrix ModelViewMatrix();
};

