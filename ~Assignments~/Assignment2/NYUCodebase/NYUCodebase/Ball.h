#pragma once
#include "TactileEntity.h"

class Ball : TactileEntity
{
public:
	Ball();

	virtual void tick(uint32_t);

	virtual void setup();
	virtual void draw();

	virtual void collision(Tactile*, uint8_t);

	void score();
	void start(uint8_t);

	using Tactile::noCollisionWith;

private:
	const float xinit, yinit;
	float xdir, ydir, spd;
	float elapsed;
};