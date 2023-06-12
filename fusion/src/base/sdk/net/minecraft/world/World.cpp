#include "World.h"

#include "../../../sdk.h"
#include "../../../../java/java.h"
#include "../../../java/util/List.h"
#include "../util/Vec3.h"
#include "../util/MovingObjectPosition.h"

#include "../../../../util/logger.h"

CWorld::CWorld() 
{
	Java::AssignClass("net.minecraft.world.World", this->Class);
	this->FieldIDs["playerEntities"] = Java::Env->GetFieldID(this->Class, "playerEntities", "Ljava/util/List;");

	this->MethodIDs["rayTraceBlocks"] = Java::Env->GetMethodID(this->Class, "rayTraceBlocks", "(Lnet/minecraft/util/Vec3;Lnet/minecraft/util/Vec3;ZZZ)Lnet/minecraft/util/MovingObjectPosition;");
}

jclass CWorld::GetClass()
{
	return this->Class;
}

jobject CWorld::GetInstance()
{
	return Java::Env->GetObjectField(SDK::Minecraft->GetInstance(), SDK::Minecraft->FieldIDs["theWorld"]);
}

std::vector<CEntityPlayer> CWorld::GetPlayerList()
{
	std::vector<CEntityPlayer> finalList;
	jobject playerEntitiesList = Java::Env->GetObjectField(this->GetInstance(), this->FieldIDs["playerEntities"]);
	jobjectArray playerEntities = List::List(playerEntitiesList).toArray();
	int size = Java::Env->GetArrayLength(playerEntities);
	
	for (int i = 0; i < size; i++)
	{
		jobject obj_player = Java::Env->GetObjectArrayElement(playerEntities, i);
		if (!obj_player) continue;

		CEntityPlayer player =  CEntityPlayer::CEntityPlayer(obj_player);
		finalList.push_back(player);
	}

	Java::Env->DeleteLocalRef(playerEntitiesList);
	Java::Env->DeleteLocalRef(playerEntities);

	return finalList;
}

Vector3 CWorld::rayTraceBlocks(Vector3 from, Vector3 to, bool stopOnLiquid, bool ignoreBlockWithoutBoundingBox, bool returnLastUncollidableBlock)
{
	// SPECIAL CASE
	jclass cls;
	Java::AssignClass("net.minecraft.util.Vec3", cls);
	jmethodID init = Java::Env->GetMethodID(cls, "<init>", "(DDD)V");
	jobject j_to = Java::Env->NewObject(cls, init, (jdouble)(double)to.x, (jdouble)(double)to.y, (jdouble)(double)to.z);
	jobject j_from = Java::Env->NewObject(cls, init, (jdouble)(double)from.x, (jdouble)(double)from.y, (jdouble)(double)from.z);

	jobject movingObjPos_j = Java::Env->CallObjectMethod(
		this->GetInstance(),
		this->MethodIDs["rayTraceBlocks"],
		j_from,
		j_to,
		stopOnLiquid,
		ignoreBlockWithoutBoundingBox,
		returnLastUncollidableBlock
	);

	if (movingObjPos_j == NULL) {
		Java::Env->DeleteLocalRef(j_to);
		Java::Env->DeleteLocalRef(j_from);
		Java::Env->DeleteLocalRef(cls);
		return Vector3(0,0,0);
	}

	CMovingObjectPosition movingObjPos = CMovingObjectPosition(movingObjPos_j);
	CVec3 a = movingObjPos.GetBlockPosition();
	Vector3 blockPos = a.GetNativeVector3();
	Java::Env->DeleteLocalRef(j_to);
	Java::Env->DeleteLocalRef(j_from);
	Java::Env->DeleteLocalRef(cls);
	return blockPos;
}
