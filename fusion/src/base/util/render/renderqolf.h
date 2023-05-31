#pragma once

#include "../../../../ext/imgui/imgui.h"

// Render quality of life functions

class RenderQOLF {
public:
	static void DrawOutlinedText(ImFont* font, float textSize, ImVec2 pos, ImColor color, ImColor outlineColor, const char* text) {
		ImGui::GetWindowDrawList()->AddText(font, textSize, ImVec2(pos.x + 1, pos.y), outlineColor, text);
		ImGui::GetWindowDrawList()->AddText(font, textSize, ImVec2(pos.x - 1, pos.y), outlineColor, text);
		ImGui::GetWindowDrawList()->AddText(font, textSize, ImVec2(pos.x, pos.y + 1), outlineColor, text);
		ImGui::GetWindowDrawList()->AddText(font, textSize, ImVec2(pos.x, pos.y - 1), outlineColor, text);

		ImGui::GetWindowDrawList()->AddText(font, textSize, pos, color, text);
	}
};