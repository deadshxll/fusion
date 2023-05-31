#pragma once

#include "../IClass.h"


struct String : IClass
{
	String(jobject instance);

	String(std::string text);

	jclass GetClass();
	jobject GetInstance();


	std::string ToString();
};

