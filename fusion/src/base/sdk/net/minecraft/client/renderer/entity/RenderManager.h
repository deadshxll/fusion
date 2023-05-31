#pragma once

#include "../../../../../java/IClass.h"
#include "../../../../../../util/math/geometry.h"

struct CRenderManager : IClass
{
	CRenderManager();

	jclass GetClass();
	jobject GetInstance();

	Vector3 RenderPos();
	Vector3 ViewerPos();
};

