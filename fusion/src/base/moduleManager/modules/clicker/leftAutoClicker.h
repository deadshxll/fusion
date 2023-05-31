#pragma once
struct LeftAutoClicker
{
	inline static bool Enabled = false;

	inline static float leftMaxCps = 10;
	inline static float leftMinCps = 10;

	static void Update();
	static void RenderMenu();
};

