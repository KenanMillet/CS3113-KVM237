#pragma once
#include "TactileEntity.h"
#include "EventDependent.h"

class Thing : public TactileEntity, public EventDependent
{
public:
	Thing(int);

	virtual void eventFilter(SDL_Event);

	virtual void setup();
	virtual void draw();

	virtual void tick(uint32_t);

	virtual void collision(Tactile*, uint8_t);
private:
	float dirX, dirY;
	const SDL_Scancode up, down, left, right;
	float elapsed;
	float spd;
};