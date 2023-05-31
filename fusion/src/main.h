#pragma once

#include <Windows.h>
#include "base/base.h"

class Main
{
public:
	static void Init();
	static void Kill();

	static inline HMODULE HModule;
};

