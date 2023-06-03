#pragma once
struct LeftAutoClicker
{
	inline static bool Enabled = false;

	inline static float leftMaxCps = 14;
	inline static float leftMinCps = 8;
	inline static bool ignoreBlocks = true;

	static void Update();
	static void RenderMenu();
};

