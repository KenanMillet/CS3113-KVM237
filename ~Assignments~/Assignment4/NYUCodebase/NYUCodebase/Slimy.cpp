#include "Slimy.h"
#include "Entities.h"
#include "Texture.h"

Slimy::Slimy()
	:	TactileEntity::Model("slimeWalk1.png", getSpriteSheet("enemies.png", "enemies.xml")),
		TactileEntity::Tactile(width(), height()),
		grounded(false), dead(false), accelx(3.0f)
{
}

void Slimy::setup()
{
	if(dead)
	{
		xPos = -1000.0f;
		yPos = -1000.0f;
		dispX = 0.0f;
		dispY = 0.0f;
	}

	if(velx == 0.0f) accelx *= -1.0f;
	float g = -9.8f * elapsed;
	float fr = ((accelx == 0.0f) ? 10.0f * elapsed : 0.0f);
	vely += accely * elapsed;
	velx += accelx * elapsed;
	if(!grounded) vely += g;
	if(grounded)
	{
		if(fabsf(velx) - fr < 0.0f) velx = 0.0f;
		else if(velx < 0) velx += fr;
		else velx -= fr;
	}
	if(fabsf(velx) > 2.0f) velx = 2.0f * ((velx < 0.0f) ? -1.0f : 1.0f);

	dispY = vely * elapsed;
	dispX = velx * elapsed;
}

void Slimy::draw()
{
	resetPosition().move(xPos, yPos, 0).scale(-1.0f * fabsf(accelx)/accelx,1.0f, 1.0f);
}

void Slimy::tick(uint32_t e)
{
	if(dead) return;
	elapsed = float(e) / 1000.0f;
	grounded = false;
}

void Slimy::touch(Tactile* t, uint8_t sides)
{
	if(dead) return;

	if(((sides & 4U) != 0) && (vely < 0.0f)) vely = 0.0f;
	if(((sides & 8U) != 0) && (vely > 0.0f)) vely = 0.0f;

	if(((sides & 1U) != 0) && (velx < 0.0f)) velx = 0.0f;
	if(((sides & 2U) != 0) && (velx > 0.0f)) velx = 0.0f;

	if(((sides & 8U) != 0) && t->isOfType<Player>()) dead = true;

	grounded = ((sides & 4U) != 0);
}
