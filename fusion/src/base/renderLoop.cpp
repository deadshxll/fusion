#include "base.h"
#include "sdk/sdk.h"

#include "moduleManager/modules/visual/esp.h"
#include "moduleManager/modules/combat/aimAssist.h"

#include "../../ext/imgui/imgui.h"
#include "menu/menu.h"

void Base::RenderLoop() // Runs every frame
{
	if (!Base::Running) return;
	const char* watermark = "fusion by deity & deadshxll";
	// goofy ahh css
	float margin = 3;
	float font_size = 24;

	ImVec2 screenSize = ImGui::GetWindowSize();
	ImVec2 textSize = Menu::Font->CalcTextSizeA(font_size, FLT_MAX, 0.0f, watermark);
	float posX = screenSize.x - textSize.x - margin;
	float posY = screenSize.y - textSize.y - margin;
	ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX + 1, posY), ImColor(255,255,255), watermark);
	ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX - 1, posY), ImColor(255, 255, 255), watermark);
	ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX, posY + 1), ImColor(255, 255, 255), watermark);
	ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX, posY - 1), ImColor(255, 255, 255), watermark);

	ImGui::GetWindowDrawList()->AddText(Menu::Font, font_size, ImVec2(posX, posY), ImColor(0, 0, 0), watermark);

	Esp::RenderUpdate();
	AimAssist::RenderUpdate();
}