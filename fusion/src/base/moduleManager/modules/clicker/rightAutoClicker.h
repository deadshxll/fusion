#pragma once
struct RightAutoClicker
{
	inline static bool Enabled = false;

	inline static float rightMaxCps = 10;
	inline static float rightMinCps = 10;

	static void Update();
	static void RenderMenu();
};

