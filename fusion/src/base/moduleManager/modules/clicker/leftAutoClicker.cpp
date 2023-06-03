#include "leftAutoClicker.h"
#include "../../../sdk/sdk.h"
#include "../../../menu/menu.h"
#include "../../../util/logger.h"
#include "../../../menu/menu.h"

#include <chrono>
#include <random>

long lastClickTime = 0;
int nextCps = 10;

void LeftAutoClicker::Update()
{
	if (!Enabled) return;
	if (Menu::Open) return;
	if (SDK::Minecraft->IsInGuiState()) return;
	if (ignoreBlocks && SDK::Minecraft->GetMouseOver().IsTypeOfBlock()) return;

	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (lastClickTime == 0) lastClickTime = milli;
	if ((milli - lastClickTime) < (1000 / nextCps)) return;

	if (GetAsyncKeyState(VK_LBUTTON) && 1) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		SendMessage(Menu::HandleWindow, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_LBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

		lastClickTime = milli;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(LeftAutoClicker::leftMinCps , LeftAutoClicker::leftMaxCps);
		nextCps = distrib(gen);
	}
}

void LeftAutoClicker::RenderMenu()
{
	ImGui::BeginGroup();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 20);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
	if (ImGui::BeginChild("autoclicker", ImVec2(425, 130))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(857834, "Toggle Left Auto Clicker", &LeftAutoClicker::Enabled);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		Menu::DoSliderStuff(3280, "Min CPS", &LeftAutoClicker::leftMinCps, 1, LeftAutoClicker::leftMaxCps);
		Menu::DoSliderStuff(675, "Max CPS", &LeftAutoClicker::leftMaxCps, LeftAutoClicker::leftMinCps, 20);
		Menu::DoToggleButtonStuff(2136, "Ignore Blocks", &LeftAutoClicker::ignoreBlocks);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::EndGroup();
}