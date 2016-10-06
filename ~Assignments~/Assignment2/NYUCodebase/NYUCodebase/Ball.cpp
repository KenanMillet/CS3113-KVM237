#include "Ball.h"

Ball::Ball()
	: TactileEntity::Tactile(0.1f, 0.1f), TactileEntity::Model("ball.png", { -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f }, { 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f }),
		xinit(0.0f), yinit(0.0f), xdir(0.0f), ydir(0.0f), spd(2.0f)
{
}

void Ball::tick(uint32_t elapsed)
{
	this->elapsed = float(elapsed)/1000.0f;
}

void Ball::setup()
{
	x += xdir * elapsed * spd;
	y += ydir * elapsed * spd;
}

void Ball::draw()
{
	reset().move(x, y, 0.0f).scale(0.2f, 0.2f, 0.0f);
}

void Ball::collision(Tactile* t, uint8_t sides)
{
	if(sides & (3 << 0))
	{
		if(sides & (1 << 0)) xdir = 1;
		if(sides & (1 << 1)) xdir = -1;
		x = t->getX() + xdir * (t->getCollW() + getCollW())/2;
	}
	if(sides & (3 << 2))
	{
		if(sides & (1 << 2)) ydir = 1;
		if(sides & (1 << 3)) ydir = -1;
		y = t->getY() + ydir * (t->getCollH() + getCollH())/2;
	}
}

void Ball::score()
{
	x = xinit;
	y = yinit;
	xdir = 0.0f;
	ydir = 0.0f;
	spd += 0.1f;
}

void Ball::start(uint8_t player)
{
	xdir = float((player * 2) - 3);
	ydir = xdir;
}