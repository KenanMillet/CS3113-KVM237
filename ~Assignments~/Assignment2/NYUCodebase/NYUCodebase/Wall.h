#pragma once
#include "TactileEntity.h"

class Wall : TactileEntity
{
public:
	Wall(float, float);
	virtual void collision(Tactile*, uint8_t);
	virtual void draw();
	virtual void tick(uint32_t);
};