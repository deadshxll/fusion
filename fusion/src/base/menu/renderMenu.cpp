#include "menu.h"
#include "../../main.h"

#include "../../../ext/imgui/imgui.h"
#include "../../../ext/imgui/imgui_internal.h"
#include "../../../ext/imgui/imgui_impl_win32.h"
#include "../../../ext/imgui/imgui_impl_opengl2.h"

#include "../util/window/borderless.h"

#include "../moduleManager/modules/visual/esp.h"
#include "../moduleManager/modules/combat/aimAssist.h"
#include "../moduleManager/modules/combat/reach.h"
#include "../moduleManager/modules/clicker/leftAutoClicker.h"
#include "../moduleManager/modules/clicker/rightAutoClicker.h"

#include "../sdk/net/minecraft/client/Minecraft.h"
#include "../util/logger.h"

int currentTab = -1;

/*

DO NOT COPY & PASTE FUSIONS MENU!

Fusions menu is really not flexible at all, I *highly* discourage copying and pasting from fusions menu.
Although it looks good, it was my (deadshell's) first time making an imgui menu and it was kind of rushed to release fusion.

*/


void Menu::RenderMenu()
{
	ImGui::SetNextWindowSize(ImVec2(575, 300));
	ImGui::Begin(Menu::Title.c_str(), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	ImVec2 idk = ImGui::GetWindowSize();

	int buttonAmount = 6;
	int buttonHeight = 20;
	ImGui::PushID("Start");
	ImGui::Columns(2, "stuff");
	float columnWidth = 110;
	ImGui::SetColumnWidth(0, columnWidth);
	//ImGui::GetWindowDrawList()->AddText(Menu::Font, distTextSize, ImVec2(posX, posY), ImColor();
	ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 textSize = Menu::FontBold->CalcTextSizeA(28, FLT_MAX, 0.0f, "FUSION");
	float posX = windowPos.x + (columnWidth / 2) - (textSize.x / 2);
	float posY = windowPos.y + 20;

	Menu::GlitchText("FUSION", ImVec2(posX, posY));
	ImGui::SetCursorPosY(textSize.y + 30);

	if (Menu::TabButton("Visual", (currentTab == 0 ? ImVec4(0.3f, 0.3f, 0.3f,0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab = 0;
	if (Menu::TabButton("Combat", (currentTab == 1 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab = 1;
	if (Menu::TabButton("Clicker", (currentTab == 2 ? ImVec4(0.3f, 0.3f, 0.3f, 0.2f) : ImVec4(0.1f, 0.1f, 0.1f, 0.f)))) currentTab = 2;


	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 5));
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.64, 0.2, 0.2, 0.5));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.74, 0.4, 0.4, 1));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 0.4, 0.4, 1));

	ImGui::SetCursorPos(ImVec2(17.5, ImGui::GetCursorPosY() + 85));
	if (ImGui::Button("Detach"))
	{
		Base::Running = false;
	}

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::PopStyleVar();

	ImGui::InvisibleButton("", ImVec2(1, idk.y));
	ImGui::NextColumn();

	if (ImGui::BeginChild("child_2", { 0, 0 }, false)) {

		ImGui::PushID("menus");

		if (currentTab == 0)
		{
			Esp::RenderMenu();
			ImGui::InvisibleButton("", ImVec2(1, 100));
		}

		if (currentTab == 1)
		{
			AimAssist::RenderMenu();
			Reach::RenderMenu();
			ImGui::InvisibleButton("", ImVec2(1, 100));
		}

		if (currentTab == 2)
		{
			LeftAutoClicker::RenderMenu();
			RightAutoClicker::RenderMenu();
			ImGui::InvisibleButton("", ImVec2(1, 100));
		}

		ImGui::PopID();

		ImGui::EndChild();
	}
	ImGui::PopID();

	ImGui::End();
}