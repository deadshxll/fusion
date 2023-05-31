#pragma once

#include "../IClass.h"

struct List : IClass
{
	List(jobject jlist);

	jclass GetClass();
	jobject GetInstance();

	jobjectArray toArray();
};

