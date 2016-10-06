#include "Paddle.h"
#include "Ball.h"

Paddle::Paddle(SDL_Scancode up, SDL_Scancode down, float xinit, Ball* ball, uint8_t player)
	:	TactileEntity::Tactile(0.2, 0.8), TactileEntity::Model("paddle.png", { -1, -4, 1, -4, 1, 4, -1, -4, 1, 4, -1, 4 }, { 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0 }),
		EventDependent({ SDL_KEYDOWN, SDL_KEYUP }), up(up), down(down), dir(0), yinit(0), spd(2), ball(ball), wait(true), player(player)
{
	x = xinit;
}

void Paddle::tick(uint32_t elapsed)
{
	obstruction = 0;
	this->elapsed = float(elapsed)/1000.0f;
}

void Paddle::eventFilter(SDL_Event event)
{
	if(event.key.keysym.scancode == up)
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				dir = ((obstruction == 1) ? 0 : 1);
				break;
			case SDL_KEYUP:
				dir = 0;
				break;
		}
	}
	if(event.key.keysym.scancode == down)
	{
		switch(event.type)
		{
			case SDL_KEYDOWN:
				dir = ((obstruction == -1) ? 0 : -1);
				break;
			case SDL_KEYUP:
				dir = 0;
				break;
		}
	}
	if(wait)
	{
		ball->start(player);
		wait = false;
	}
}

void Paddle::setup()
{
	y += spd * elapsed * dir;
}

void Paddle::draw()
{
	reset().move(x, y, 0).scale(0.1, 0.1, 0);
}

void Paddle::collision(Tactile* t, uint8_t sides)
{
	if(sides & (1 << 3)) obstruction = 1;
	if(sides & (1 << 2)) obstruction = -1;
}

void Paddle::score()
{
	wait = true;
}
