#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>

struct Reach
{
	inline static bool Enabled = false;

	inline static float ReachDistance = .5f;

	static void Update();

	static void RenderMenu();
};

