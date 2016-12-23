#include "Test.h"
#include "Texture.h"

Thing::Thing(int i)
	:	TactileEntity::Model(((i==0) ? "playerShip3_blue.png" :"playerShip3_red.png"), getSpriteSheet("sheet.png", "sheet.xml"), 0.5f),
		TactileEntity::Tactile(width(), height()),
		EventDependent({ SDL_KEYDOWN, SDL_KEYUP }),
		up(((i==0) ? SDL_SCANCODE_UP : SDL_SCANCODE_W)), down(((i == 0) ? SDL_SCANCODE_DOWN : SDL_SCANCODE_S)),
		left(((i == 0) ? SDL_SCANCODE_LEFT : SDL_SCANCODE_A)), right(((i == 0) ? SDL_SCANCODE_RIGHT : SDL_SCANCODE_D)),
		spd(2.0f)
{
}

void Thing::eventFilter(SDL_Event event)
{
	SDL_Scancode scancode = event.key.keysym.scancode;
	Uint32 type = event.type;
	if(scancode == up)
	{
		if(type == SDL_KEYDOWN) dirY = 1.0f;
		if(type == SDL_KEYUP) dirY = 0.0f;
	}
	if(scancode == down)
	{
		if(type == SDL_KEYDOWN) dirY = -1.0f;
		if(type == SDL_KEYUP) dirY = 0.0f;
	}
	if(scancode == left)
	{
		if(type == SDL_KEYDOWN) dirX = -1.0f;
		if(type == SDL_KEYUP) dirX = 0.0f;
	}
	if(scancode == right)
	{
		if(type == SDL_KEYDOWN) dirX = 1.0f;
		if(type == SDL_KEYUP) dirX = 0.0f;
	}
}

void Thing::setup()
{
	dispX = spd * elapsed * dirX;
	dispY = spd * elapsed * dirY;
}

void Thing::draw()
{
	resetPosition().move(xPos, yPos, 0);
}

void Thing::tick(uint32_t e)
{
	elapsed = float(e) / 1000.0f;
}

void Thing::collision(Tactile *, uint8_t)
{
}
