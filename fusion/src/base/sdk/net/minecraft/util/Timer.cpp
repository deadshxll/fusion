#include "Timer.h"

#include "../../../../java/java.h"
#include "../../../sdk.h"

CTimer::CTimer()
{
	Java::AssignClass("net.minecraft.util.Timer", this->Class);
	this->FieldIDs["renderPartialTicks"] = Java::Env->GetFieldID(this->Class, "renderPartialTicks", "F");
}

float CTimer::GetRenderPartialTicks()
{
	return Java::Env->GetFloatField(this->GetInstance(), this->FieldIDs["renderPartialTicks"]);
}

jclass CTimer::GetClass()
{
	return this->Class;
}

jobject CTimer::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["timer"]);
}