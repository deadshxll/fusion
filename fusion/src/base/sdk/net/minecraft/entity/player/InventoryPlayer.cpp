#include "InventoryPlayer.h"

#include "../../../../strayCache.h"

CInventoryPlayer::CInventoryPlayer()
{
	if (!StrayCache::initialized) StrayCache::Initialize();
	this->Class = StrayCache::inventoryPlayer_class;
}

CInventoryPlayer::CInventoryPlayer(jobject instance) : CInventoryPlayer()
{
	this->Instance = instance;
}

jclass CInventoryPlayer::GetClass()
{
	return this->Class;
}

jobject CInventoryPlayer::GetInstance()
{
	return this->Instance;
}

CItemStack CInventoryPlayer::GetCurrentItem()
{
	return CItemStack(Java::Env->CallObjectMethod(this->GetInstance(), StrayCache::inventoryPlayer_getCurrentItem));
}
