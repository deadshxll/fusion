#pragma once
#include <iostream>
#include <string>
#include "../util/math/geometry.h"

struct Logger
{
	static void Init();
	static void Kill();

	static void Log(std::string message);
	static void LogPosition(Vector3 message);
	static void Err(std::string message);

	static void LogWait(std::string message, int seconds=1);
	static void ErrWait(std::string message, int seconds=1);

	static inline bool Initialized = false;;
};

