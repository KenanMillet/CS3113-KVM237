#pragma once

#include "TactileEntity.h"

class Slimy : public TactileEntity
{
public:
	Slimy();

	virtual void setup();
	virtual void draw();

	virtual void tick(uint32_t);

	virtual void touch(Tactile*, uint8_t);

private:
	float accelx, accely, velx, vely;
	bool grounded;
	bool dead;
	float elapsed;
};