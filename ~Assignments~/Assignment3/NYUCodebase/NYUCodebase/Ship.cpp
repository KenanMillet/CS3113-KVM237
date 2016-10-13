#include "Ship.h"
#include "Texture.h"
#include "Bullet.h"
#include "Enemy.h"

Ship::Ship()
	:	TactileEntity::Model("playerShip3_red.png", getSpriteSheet("sheet.png", "sheet.xml"), 0.5f),
		TactileEntity::Tactile(width(), height()),
		EventDependent({ SDL_KEYDOWN, SDL_KEYUP }),
		dir(0.0f), spd(2.0f), elapsed(0.0f), bullet(new Bullet(this, 1.0f)), lives(3)
{

}

void Ship::eventFilter(SDL_Event event)
{
	if(destroyed) return;

	switch(event.key.keysym.scancode)
	{
		case SDL_SCANCODE_LEFT:
			switch(event.type)
			{
				case SDL_KEYDOWN:
					dir = -1.0f;
					break;
				case SDL_KEYUP:
					dir = 0.0f;
					break;
			}
			break;
		case SDL_SCANCODE_RIGHT:
			switch(event.type)
			{
				case SDL_KEYDOWN:
					dir = 1.0f;
					break;
				case SDL_KEYUP:
					dir = 0.0f;
					break;
			}
			break;
		case SDL_SCANCODE_SPACE:
			switch(event.type)
			{
				case SDL_KEYDOWN:
					if(!(bullet->active())) fire();
					break;
			}
			break;
	}
}

void Ship::setup()
{
	if(destroyed)
	{
		xPos = -1000.0f;
		yPos = -1000.0f;
		return;
	}
	xPos += spd * elapsed * dir;
}

void Ship::draw()
{
	resetPosition().move(xPos, yPos, 0);
}

void Ship::tick(uint32_t e)
{
	elapsed = float(e) / 1000.0f;
}

void Ship::collision(Tactile* t, uint8_t)
{
	if(t->isOfType<Enemy>()) lives = 0;
	if(t->isOfType<Bullet>())
	{
		if(dynamic_cast<Bullet*>(t)->dir < 0) --lives;
	}
	destroyed = (lives == 0);
}

void Ship::fire()
{
	bullet->level = level;
	bullet->activate();
}