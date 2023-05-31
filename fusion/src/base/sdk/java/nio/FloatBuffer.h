#pragma once

#include "../IClass.h"
#include "../../../util/math/geometry.h"

struct FloatBuffer : IClass
{
	FloatBuffer(jobject obj);

	jclass GetClass();
	jobject GetInstance();

	Matrix GetMatrix();
};

