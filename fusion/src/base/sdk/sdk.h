#pragma once

#include "net/minecraft/client/Minecraft.h"

struct SDK
{
	static inline CMinecraft* Minecraft;

	static void Init();
};

