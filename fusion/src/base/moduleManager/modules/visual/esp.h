#pragma once
#include "../../../util/math/geometry.h"

#include <vector>
#include <string>

struct Esp
{
	inline static bool Enabled = true;

	struct Data {
		std::vector<Vector3> boxVerticies;
		std::string name;
		std::string distText;
		float dist;
		float opacityFadeFactor;
		float health;
		float maxHealth;
	};

	inline static std::vector<Data> renderData;

	inline static bool Box = true;
	inline static float BoxColor[4]{ 0, 0, 0, 1 };

	inline static bool FilledBox = true;
	inline static float FilledBoxColor[3]{ 0, 0, 0 };
	inline static float SecondFilledBoxColor[3]{ 0, 0, 0 };
	inline static float FilledBoxOpacity = 0.15f;

	inline static bool Outline = true;
	inline static float OutlineColor[4]{ 0, 0, 0, 0.25 };

	inline static bool Text = true;
	inline static float TextSize = 18;
	inline static float TextColor[4]{ 1.0f, 1.0f, 1.0f, 1.0f };
	inline static bool TextOutline = true;
	inline static float TextOutlineColor[4]{ 0, 0, 0, 1.0f };
	inline static float TextUnrenderDistance = 14.0f;

	inline static float FadeDistance = 3.0f;

	inline static bool HealthBar = true;


	static void Update();

	static void RenderUpdate();
	static void RenderMenu();
};