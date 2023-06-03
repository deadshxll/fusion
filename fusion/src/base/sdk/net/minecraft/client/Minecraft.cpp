#include "Minecraft.h"
#include "../../../../java/java.h"
#include "../../../../util/logger.h"

#include "../entity/EntityLivingBase.h"

CMinecraft::CMinecraft()
{
	Java::AssignClass("net.minecraft.client.Minecraft", this->Class);

	this->MethodIDs["getMinecraft"] = Java::Env->GetStaticMethodID(this->GetClass(), "getMinecraft", "()Lnet/minecraft/client/Minecraft;");
	this->Instance = Java::Env->CallStaticObjectMethod(this->GetClass(), this->MethodIDs["getMinecraft"]);

	this->FieldIDs["thePlayer"] = Java::Env->GetFieldID(this->GetClass(), "thePlayer", "Lnet/minecraft/client/entity/EntityPlayerSP;");
	this->thePlayer = new CEntityPlayerSP();

	this->FieldIDs["theWorld"] = Java::Env->GetFieldID(this->GetClass(), "theWorld", "Lnet/minecraft/client/multiplayer/WorldClient;");
	this->theWorld = new CWorldClient();

	this->activeRenderInfo = new CActiveRenderInfo();

	this->FieldIDs["renderManager"] = Java::Env->GetFieldID(this->GetClass(), "renderManager", "Lnet/minecraft/client/renderer/entity/RenderManager;");
	this->renderManager = new CRenderManager();

	this->FieldIDs["timer"] = Java::Env->GetFieldID(this->GetClass(), "timer", "Lnet/minecraft/util/Timer;");
	this->timer = new CTimer();

	this->FieldIDs["gameSettings"] = Java::Env->GetFieldID(this->GetClass(), "gameSettings", "Lnet/minecraft/client/settings/GameSettings;");
	this->gameSettings = new CGameSettings();

	this->MethodIDs["getRenderViewEntity"] = Java::Env->GetMethodID(this->GetClass(), "getRenderViewEntity", "()Lnet/minecraft/entity/Entity;");
	this->FieldIDs["currentScreen"] = Java::Env->GetFieldID(this->GetClass(), "currentScreen", "Lnet/minecraft/client/gui/GuiScreen;");

	this->FieldIDs["objectMouseOver"] = Java::Env->GetFieldID(this->GetClass(), "objectMouseOver", "Lnet/minecraft/util/MovingObjectPosition;");

	// not used lol
	this->MethodIDs["clickMouse"] = Java::Env->GetMethodID(this->GetClass(), "clickMouse", "()V");
}

jclass CMinecraft::GetClass()
{
	return this->Class;
}

jobject CMinecraft::GetInstance()
{
	return this->Instance;
}

CEntity CMinecraft::GetRenderViewEntity()
{
	return CEntity(Java::Env->CallObjectMethod(this->GetInstance(), this->MethodIDs["getRenderViewEntity"]));
}

bool CMinecraft::IsInGuiState()
{
	if (Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["currentScreen"]) != NULL) return true;
	return false;
}

void CMinecraft::ClickMouse()
{
	Java::Env->CallVoidMethod(this->GetInstance(), this->MethodIDs["clickMouse"]);
}

CMovingObjectPosition CMinecraft::GetMouseOver()
{
	return CMovingObjectPosition(Java::Env->GetObjectField(this->Instance, this->FieldIDs["objectMouseOver"]));
}
