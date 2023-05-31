#pragma once

#include "../../entity/player/EntityPlayer.h"

struct CEntityPlayerSP : CEntityPlayer
{
	CEntityPlayerSP();

	jclass GetClass();
	jobject GetInstance();
};