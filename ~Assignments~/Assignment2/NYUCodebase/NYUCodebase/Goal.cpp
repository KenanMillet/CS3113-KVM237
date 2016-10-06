#include "Goal.h"
#include "Ball.h"
#include "Paddle.h"

Goal::Goal(float xpos, float h, Ball* ball, Paddle* paddle)
	:	TactileEntity::Tactile(0.5, h), TactileEntity::Model("wall.png", { -3.6f, -0.25f, 3.6f, -0.25f, 3.6f, 0.25f, -3.6f, -0.25f, 3.6f, 0.25f, -3.6f, 0.25f }, { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 }),
		ball(ball), paddle(paddle)
{
	ball->noCollisionWith(this);
	x = xpos;
}

void Goal::collision(Tactile* t, uint8_t sides)
{
	ball->score();
	paddle->score();
}

void Goal::draw()
{
	reset().move(x, 0, 0).scale(0, 0, 0);
}

void Goal::tick(uint32_t)
{
}
