#pragma once
#include "../../../util/math/geometry.h"

#include <string>
#include <vector>

struct AimAssist
{

	inline static Vector3 renderData;

	inline static bool Enabled = false;

	inline static bool visibilityCheck = true;
	inline static bool aimAssistFeedback = true;
	inline static bool fovCircle = true;

	inline static Vector3 data;
	inline static bool pitchInfluenced = false;
	inline static bool aimKey = true;

	inline static bool adaptive = true;
	inline static float adaptiveOffset = 3;

	inline static float fov = 35.0f;
	inline static float smooth = 15.f;
	inline static float aimDistance = 4.f;
	inline static float randomYaw = 2;
	inline static float randomPitch = .075f;

	inline static int targetPriority = 2;
	inline static const char* targetPriorityList[3] { "Distance", "Health", "Closest to Crosshair"};


	static void Update();

	static void RenderUpdate();
	static void RenderMenu();
};

