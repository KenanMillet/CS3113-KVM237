#pragma once

#include "TactileEntity.h"
#include "EventDependent.h"

class Player : public TactileEntity, public EventDependent
{
public:
	Player();

	virtual void eventFilter(SDL_Event);

	virtual void setup();
	virtual void draw();

	virtual void tick(uint32_t);

	virtual void touch(Tactile*, uint8_t);

private:
	float accelx, accely, velx, vely;
	bool grounded;
	bool jump;
	float elapsed;
};