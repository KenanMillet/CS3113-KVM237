#pragma once
#include "TactileEntity.h"

class Block : public TactileEntity
{
public:
	Block();

	virtual void draw();

	virtual void tick(uint32_t);

	virtual void collisionX(Tactile*, uint8_t);
	virtual void collisionY(Tactile*, uint8_t);
	virtual void collisionZ(Tactile*, uint8_t);
};