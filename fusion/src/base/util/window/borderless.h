#pragma once
#include <Windows.h>

struct Borderless
{
	static void Enable(HWND hWindow);
    static void Restore(HWND hWindow);

    inline static bool Enabled = false;

    static inline LONG_PTR OriginalStyle;
};