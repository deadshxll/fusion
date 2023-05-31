#include "sdk.h"
#include "../util/logger.h"
#include "../java/java.h"
#include "strayCache.h"

void SDK::Init()
{
	StrayCache::Initialize();
	SDK::Minecraft = new CMinecraft();
}
