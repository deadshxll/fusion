#include "reach.h"
#include "../../../sdk/sdk.h"
#include "../../commonData.h"
#include "../../../util/logger.h"
#include "../../../java/java.h"
#include "../../../util/math/math.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"
#include "../../../patcher/patcher.h"

#include <chrono>


//https://github.com/Lefraudeur/RiptermsGhost

std::chrono::steady_clock::time_point lastUpdate;
void Reach::Update()
{
	static float prev_reach = -1.0f;
	if (!Enabled)
	{
		if (!CommonData::SanityCheck()) return;
		if (prev_reach != -1.0f)
		{
			Patcher::put("reach_distance", "3.0");
			prev_reach = -1.0f;
		}
		return;
	}
	if (prev_reach == Reach::ReachDistance || !CommonData::SanityCheck())
		return;
	prev_reach = ReachDistance;
	Patcher::put("reach_distance", std::to_string(ReachDistance));
}


void Reach::RenderMenu()
{

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	if (ImGui::BeginChild("reach", ImVec2(425, 75)))
	{

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
		Menu::DoToggleButtonStuff(230044, "Toggle Reach", &Reach::Enabled);

		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
		ImGui::Separator();
		Menu::DoSliderStuff(560117, "Reach Distance", &Reach::ReachDistance, 0, 4);

	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

}
