#include "reach.h"
#include "../../../sdk/sdk.h"
#include "../../commonData.h"
#include "../../../util/logger.h"
#include "../../../java/java.h"
#include "../../../util/math/math.h"
#include "../../../../../ext/imgui/imgui.h"
#include "../../../menu/menu.h"

#include <chrono>

//
//
// NOTICE:
//
// THIS MODULE IS PASTED FROM GASPER! ALL CREDIT FOR THIS MODULE GOES TO ZORFTW:
//
// https://github.com/zorftw/gasper-cpp
//
//

std::chrono::steady_clock::time_point lastUpdate;
void Reach::Update()
{
	if (!Enabled) return;
	if (!CommonData::SanityCheck()) return;

	std::chrono::steady_clock::time_point nanoTime = std::chrono::high_resolution_clock::now();

	// Calculate the elapsed time in nanoseconds
	float elapsed = (float) std::chrono::duration_cast<std::chrono::nanoseconds>(nanoTime - lastUpdate).count() / 1000000;
	if (elapsed < 20)
		return;
	else
		lastUpdate = nanoTime;

	CEntityPlayerSP* thePlayer = SDK::Minecraft->thePlayer;
	std::vector<CommonData::PlayerData> playerList = CommonData::nativePlayerList;
	if (playerList.empty()) return;

	Vector2 playerAngles = thePlayer->GetAngles();
	Vector3 playerPos = thePlayer->GetPos();

	//
	//
	// NOTICE:
	//
	// THIS MODULE IS PASTED FROM GASPER! ALL CREDIT FOR THIS MODULE GOES TO ZORFTW:
	//
	// https://github.com/zorftw/gasper-cpp
	//
	//


	for (CommonData::PlayerData target : playerList)
	{
		float distance = ReachDistance;
		if (Java::Env->IsSameObject(thePlayer->GetInstance(), target.obj.GetInstance())) continue;

		Vector3 targetPos = target.pos;
		BoundingBox targetBB = target.boundingBox;

		Vector3 diff = playerPos - targetPos;
		float hypothenuseDistance = (float) sqrt(pow(diff.x, 2) + pow(diff.z, 2));

		if (distance > hypothenuseDistance)
			distance -= hypothenuseDistance;

		Vector2 angles = Math::getAngles(playerPos, targetPos);
		float difference = Math::wrapAngleTo180(playerAngles.x - angles.x);

		if (std::abs(difference) > 180.0f)
			continue;

		float cos = std::cos(Math::degToRadiants(angles.x + 90.0f));
		float sin = std::sin(Math::degToRadiants(angles.x + 90.0f));
		float cosPitch = std::cos(Math::degToRadiants(angles.y));
		float sinPitch = std::sin(Math::degToRadiants(angles.y));

		float x = targetPos.x - (cos * distance * cosPitch);
		float y = targetPos.y + (distance * sinPitch);
		float z = targetPos.z - (sin * distance * cosPitch);

		float entityWidth = 0.6f;
		float bbWidth = entityWidth / 2.0f;

		BoundingBox newBB{
			(double) x - bbWidth,
			(double) y,
			//targetBB.minY,
			(double) z - bbWidth,

			(double) x + bbWidth,
			(double) y + 2,
			//targetBB.maxY,
			(double) z + bbWidth
		};

		target.obj.SetBB(newBB);
	}
}

//
//
// NOTICE:
//
// THIS MODULE IS PASTED FROM GASPER! ALL CREDIT FOR THIS MODULE GOES TO ZORFTW:
//
// https://github.com/zorftw/gasper-cpp
//
//


void Reach::RenderMenu()
{

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 0.5));
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);

	ImGui::BeginChild("reach", ImVec2(425, 75));

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3);
	Menu::DoToggleButtonStuff(230044, "Toggle Reach", &Reach::Enabled);

	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImGui::Separator();
	Menu::DoSliderStuff(560117, "Reach Distance", &Reach::ReachDistance, 0, 4);

	ImGui::EndChild();
	
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

}
