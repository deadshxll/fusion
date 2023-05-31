#include "EntityPlayerSP.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"

#include "../../../../../util/logger.h"

CEntityPlayerSP::CEntityPlayerSP() : CEntityPlayer()
{
	Java::AssignClass("net.minecraft.client.entity.EntityPlayerSP", this->Class);
}

jclass CEntityPlayerSP::GetClass()
{
	return this->Class;
}

jobject CEntityPlayerSP::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["thePlayer"]);
}
