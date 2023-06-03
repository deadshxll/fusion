#include "rightAutoClicker.h"
#include "../../../sdk/sdk.h"
#include "../../../menu/menu.h"
#include "../../../util/logger.h"
#include "../../../menu/menu.h"

#include <chrono>
#include <random>

long rightLastClickTime = 0;
int rightNextCps = 10;

void RightAutoClicker::Update()
{
	if (!Enabled) return;
	if (Menu::Open) return;
	if (SDK::Minecraft->IsInGuiState()) return;

	jclass blockClass;
	Java::AssignClass("net.minecraft.item.ItemBlock", blockClass);
	if (SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem().GetInstance() == NULL) return;
	if (blocksOnly && !Java::Env->IsInstanceOf(SDK::Minecraft->thePlayer->GetInventory().GetCurrentItem().GetItem(), blockClass)) return;

	long milli = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	if (rightLastClickTime == 0) rightLastClickTime = milli;
	if ((milli - rightLastClickTime) < (1000 / rightNextCps)) return;

	if (GetAsyncKeyState(VK_RBUTTON) && 1) {
		POINT pos_cursor;
		GetCursorPos(&pos_cursor);
		SendMessage(Menu::HandleWindow, WM_RBUTTONDOWN, MK_RBUTTON, MAKELPARAM(pos_cursor.x, pos_cursor.y));
		SendMessage(Menu::HandleWindow, WM_RBUTTONUP, 0, MAKELPARAM(pos_cursor.x, pos_cursor.y));

		rightLastClickTime = milli;

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distrib(rightMinCps, rightMaxCps);
		rightNextCps = distrib(gen);
	}
}

void RightAutoClicker::RenderMenu()
{
	ImGui::BeginGroup();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
	if (ImGui::BeginChild("rightautoclicker", ImVec2(425, 130))) {
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(2344, "Toggle Right Auto Clicker", &RightAutoClicker::Enabled);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		Menu::DoSliderStuff(3280, "Min CPS", &RightAutoClicker::rightMinCps, 1, RightAutoClicker::rightMaxCps);
		Menu::DoSliderStuff(675, "Max CPS", &RightAutoClicker::rightMaxCps, RightAutoClicker::rightMinCps, 20);
		Menu::DoToggleButtonStuff(73451, "Blocks Only", &RightAutoClicker::blocksOnly);

		ImGui::EndChild();
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
	ImGui::EndGroup();
}