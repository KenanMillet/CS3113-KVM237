#pragma once
#include "TactileEntity.h"

class Ball;
class Paddle;

class Goal : TactileEntity
{
public:
	Goal(float, float, Ball*, Paddle*);
	virtual void collision(Tactile*, uint8_t);
	virtual void draw();
	virtual void tick(uint32_t);
private:
	Ball* ball;
	Paddle* paddle;
};