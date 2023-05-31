#pragma once

#include "../../../../ext/jni/jni.h"

#include <string>
#include <map>

struct IClass
{
	std::map<std::string, jmethodID> MethodIDs;
	std::map<std::string, jfieldID> FieldIDs;

	jobject Instance = 0;
	jclass Class = 0;

	virtual jobject GetInstance() = 0;
	virtual jclass GetClass() = 0;
};

