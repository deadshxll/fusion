#pragma once

#include "../../../java/IClass.h"

struct CTimer : IClass
{
	CTimer();

	jclass GetClass();
	jobject GetInstance();

	float GetRenderPartialTicks();
};

