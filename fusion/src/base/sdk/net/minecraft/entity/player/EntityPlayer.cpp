#include "EntityPlayer.h"

#include "../../../../../java/java.h"

CEntityPlayer::CEntityPlayer(){}

CEntityPlayer::CEntityPlayer(jobject instance) : CEntityPlayer()
{
	this->Instance = instance;
}


jclass CEntityPlayer::GetClass()
{
	return this->Class;
}

jobject CEntityPlayer::GetInstance()
{
	return this->Instance;
}