#pragma once
#include "TactileEntity.h"
#include "EventDependent.h"

class Ball;

class Paddle : TactileEntity, EventDependent
{
public:
	Paddle(SDL_Scancode, SDL_Scancode, float, Ball*, uint8_t);

	virtual void tick(uint32_t);

	virtual void eventFilter(SDL_Event);

	virtual void setup();
	virtual void draw();

	virtual void collision(Tactile*, uint8_t);

	void score();
private:
	uint8_t player;
	bool wait;
	Ball* ball;
	
	int8_t obstruction;

	SDL_Scancode up, down;
	float elapsed;
	float dir;
	float yinit, spd;
};