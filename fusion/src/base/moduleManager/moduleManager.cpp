#include "moduleManager.h"

#include "modules/visual/esp.h"
#include "modules/combat/aimAssist.h"
#include "modules/combat/reach.h"
#include "modules/clicker/leftAutoClicker.h"
#include "modules/clicker/rightAutoClicker.h"
#include "commonData.h"

void ModuleManager::Init()
{
}

void ModuleManager::UpdateModules()
{
	if (!CommonData::SanityCheck()) return;

	CommonData::UpdateData();
	Esp::Update();

	AimAssist::Update();
	Reach::Update();

	LeftAutoClicker::Update();
	RightAutoClicker::Update();
}
