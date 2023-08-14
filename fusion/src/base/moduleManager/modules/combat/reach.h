#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>

struct Reach
{
	inline static bool Enabled = false;

	inline static float ReachDistance = 3.0f;

	static void Update();

	static void RenderMenu();
};

