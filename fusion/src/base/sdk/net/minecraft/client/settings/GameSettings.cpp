#include "GameSettings.h"
#include "../../../../sdk.h"
#include "../../../../../java/java.h"

CGameSettings::CGameSettings()
{
	Java::AssignClass("net.minecraft.client.settings.GameSettings", this->Class);
	this->FieldIDs["thirdPersonView"] = Java::Env->GetFieldID(this->Class, "thirdPersonView", "I");
	this->FieldIDs["fovSetting"] = Java::Env->GetFieldID(this->Class, "fovSetting", "F");

	this->FieldIDs["keyBindFullscreen"] = Java::Env->GetFieldID(this->Class, "keyBindFullscreen", "Lnet/minecraft/client/settings/KeyBinding;");
	this->MethodIDs["setOptionKeyBinding"] = Java::Env->GetMethodID(this->Class, "setOptionKeyBinding", "(Lnet/minecraft/client/settings/KeyBinding;I)V");
}

jclass CGameSettings::GetClass()
{
	return this->Class;
}

jobject CGameSettings::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["gameSettings"]);
}

float CGameSettings::GetFOV()
{
	return Java::Env->GetFloatField(GetInstance(), this->FieldIDs["fovSetting"]);
}

void CGameSettings::SetFullscreenKeyToNull()
{
	jobject instance = this->GetInstance();
	Java::Env->CallVoidMethod(instance, this->MethodIDs["setOptionKeyBinding"], Java::Env->GetObjectField(instance, this->FieldIDs["keyBindFullscreen"]), 0);
}

void CGameSettings::RestoreFullscreenKey()
{
	jobject instance = this->GetInstance();
	Java::Env->CallVoidMethod(instance, this->MethodIDs["setOptionKeyBinding"], Java::Env->GetObjectField(instance, this->FieldIDs["keyBindFullscreen"]), 87);
}


int CGameSettings::GetThirdPersonView()
{
	return Java::Env->GetIntField(GetInstance(), this->FieldIDs["thirdPersonView"]);
}

