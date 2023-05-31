#pragma once

#include "../IClass.h"

struct Set : IClass
{
	Set(jobject jlist);

	jclass GetClass();
	jobject GetInstance();

	jobjectArray toArray();
	int size();
};

