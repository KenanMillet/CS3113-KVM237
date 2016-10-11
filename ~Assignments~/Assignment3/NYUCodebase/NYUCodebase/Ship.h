#pragma once
#include "TactileEntity.h"
#include "EventDependent.h"

class Bullet;

class Ship : public TactileEntity, public EventDependent
{
	friend Bullet;
public:
	Ship();

	virtual void eventFilter(SDL_Event);

	virtual void setup();
	virtual void draw();

	virtual void tick(uint32_t);

	virtual void collision(Tactile*, uint8_t);
private:
	void fire();

	float elapsed;
	float dir, spd;
	bool destroyed;
	uint8_t lives;

	Bullet* bullet;
};