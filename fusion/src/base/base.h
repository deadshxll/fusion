#pragma once

struct Base
{
	static void Init();
	static void Kill();

	static void CheatLoop();
	static void RenderLoop();

	static inline bool Running;
};

