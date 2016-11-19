#include "Player.h"
#include "Entities.h"
#include "Texture.h"
#include <cmath>

Player::Player()
	:	TactileEntity::Model("p1_stand.png", getSpriteSheet("player.png", "player.xml")),
		TactileEntity::Tactile(width(), height()),
		EventDependent({SDL_KEYDOWN, SDL_KEYUP}),
		grounded(false)
{
}

void Player::eventFilter(SDL_Event event)
{
	SDL_Scancode scancode = event.key.keysym.scancode;
	Uint32 type = event.type;
	if(scancode == SDL_SCANCODE_W || scancode == SDL_SCANCODE_SPACE)
	{
		if(type == SDL_KEYDOWN) jump = grounded;
		if(type == SDL_KEYUP) jump = false;
	}
	if(scancode == SDL_SCANCODE_A)
	{
		if(type == SDL_KEYDOWN) accelx = -10.0f;
		if(type == SDL_KEYUP) accelx = 0.0f;
	}
	if(scancode == SDL_SCANCODE_D)
	{
		if(type == SDL_KEYDOWN) accelx = 10.0f;
		if(type == SDL_KEYUP) accelx = 0.0f;
	}
}

void Player::setup()
{
	float g = -9.8f * elapsed;
	float fr = ((accelx == 0.0f) ? 10.0f * elapsed : 0.0f);

	vely += accely * elapsed;
	velx += accelx * elapsed;

	if(jump) vely = 5.0f;
	if(!grounded) vely += g;
	if(grounded)
	{
		if(fabsf(velx) - fr < 0.0f) velx = 0.0f;
		else if(velx < 0) velx += fr;
		else velx -= fr;
	}
	if(fabsf(velx) > 5.0f) velx = 5.0f * ((velx < 0.0f) ? -1.0f : 1.0f);

	dispY = vely * elapsed;
	dispX = velx * elapsed;
}

void Player::draw()
{
	resetPosition().move(xPos, yPos, 0);
}

void Player::tick(uint32_t e)
{
	elapsed = float(e) / 1000.0f;
	grounded = false;
}

void Player::touch(Tactile* t, uint8_t sides)
{
	if(((sides & 4U) != 0) && (vely < 0.0f)) vely = 0.0f;
	if(((sides & 8U) != 0) && (vely > 0.0f)) vely = 0.0f;

	if(((sides & 1U) != 0) && (velx < 0.0f)) velx = 0.0f;
	if(((sides & 2U) != 0) && (velx > 0.0f)) velx = 0.0f;

	grounded = ((sides & 4U) != 0);
}
