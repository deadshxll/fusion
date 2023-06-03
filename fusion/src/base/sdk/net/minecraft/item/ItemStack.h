#pragma once
#include "../../../java/IClass.h"

struct CItemStack : IClass
{
	CItemStack();

	CItemStack(jobject instance);

	jclass GetClass();
	jobject GetInstance();

	jobject GetItem();
};