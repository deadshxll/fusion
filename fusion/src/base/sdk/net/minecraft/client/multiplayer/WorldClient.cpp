#include "WorldClient.h"

#include "../../../../sdk.h"
#include "../../../../../java/java.h"
#include "../../../../../util/logger.h"
#include "../../../../java/util/Set.h"

CWorldClient::CWorldClient()
{
	Java::AssignClass("net.minecraft.client.multiplayer.WorldClient", this->Class);
	Java::AssignClass("net.minecraft.entity.player.EntityPlayer", this->EntityPlayer); // doing this because am lazy
	this->FieldIDs["entityList"] = Java::Env->GetFieldID(this->Class, "entityList", "Ljava/util/Set;");
}

jclass CWorldClient::GetClass()
{
	return this->Class;
}

jobject CWorldClient::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["theWorld"]);
}

std::vector<CEntity> CWorldClient::GetEntityList()
{
	std::vector<CEntity> finalList;
	jfieldID targetField = this->FieldIDs["entityList"];

	jobject playerEntitiesList = Java::Env->GetObjectField(this->GetInstance(), targetField);

	jobjectArray playerEntities = Set::Set(playerEntitiesList).toArray();
	int size = Java::Env->GetArrayLength(playerEntities);

	for (int i = 0; i < size; i++)
	{
		jobject obj_player = Java::Env->GetObjectArrayElement(playerEntities, i);
		if (!obj_player) continue;

		CEntity player = CEntity::CEntity(obj_player);
		if (player.GetName().compare(SDK::Minecraft->thePlayer->GetName()))
			finalList.push_back(player);
	}
	return finalList;
}