#pragma once

#include <string>

#include "../../../ext/jni/jni.h"

struct Java
{
	static void Init();
	static void Kill();

	static bool AssignClass(std::string name, jclass &out);

	static inline JNIEnv* Env;
	static inline bool Initialized;
};

