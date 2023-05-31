#include "RenderManager.h"

#include "../../../../../../java/java.h"
#include "../../../../../sdk.h"

CRenderManager::CRenderManager()
{
	Java::AssignClass("net.minecraft.client.renderer.entity.RenderManager", this->Class);
	this->FieldIDs["renderPosX"] = Java::Env->GetFieldID(this->Class, "renderPosX", "D");
	this->FieldIDs["renderPosY"] = Java::Env->GetFieldID(this->Class, "renderPosY", "D");
	this->FieldIDs["renderPosZ"] = Java::Env->GetFieldID(this->Class, "renderPosZ", "D");

	this->FieldIDs["viewerPosX"] = Java::Env->GetFieldID(this->Class, "viewerPosX", "D");
	this->FieldIDs["viewerPosY"] = Java::Env->GetFieldID(this->Class, "viewerPosY", "D");
	this->FieldIDs["viewerPosZ"] = Java::Env->GetFieldID(this->Class, "viewerPosZ", "D");
}

Vector3 CRenderManager::RenderPos()
{
	jobject instance = this->GetInstance();
	return Vector3{
		(float)(double) Java::Env->GetDoubleField(instance, this->FieldIDs["renderPosX"]),
		(float)(double) Java::Env->GetDoubleField(instance, this->FieldIDs["renderPosY"]),
		(float)(double) Java::Env->GetDoubleField(instance, this->FieldIDs["renderPosZ"])
	};
}

Vector3 CRenderManager::ViewerPos()
{
	jobject instance = this->GetInstance();
	return Vector3{
		(float)(double)Java::Env->GetDoubleField(instance, this->FieldIDs["viewerPosX"]),
		(float)(double)Java::Env->GetDoubleField(instance, this->FieldIDs["viewerPosY"]),
		(float)(double)Java::Env->GetDoubleField(instance, this->FieldIDs["viewerPosZ"])
	};
}

jclass CRenderManager::GetClass()
{
	return this->Class;
}

jobject CRenderManager::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["renderManager"]);
}