#include "Bullet.h"
#include "Texture.h"
#include "Ship.h"
#include "Enemy.h"

Bullet::Bullet(TactileEntity* spawner, float dir)
	:	TactileEntity::Model(((dir > 0) ? "laserRed07.png" : "laserBlue07.png"), SpriteSheet("sheet.png", "sheet.xml"), 0.25f),
		TactileEntity::Tactile(width(), height()),
		spawner(spawner), dir(dir), spd(6.0f), hidden(true)
{
	xPos = -1000.0f;
	yPos = -1000.0f;
}

void Bullet::setup()
{
	if(dying) deactivate();
	if(hidden) return;
	yPos += dir * elapsed * spd;
	if(outOfBoundsNorth() || outOfBoundsSouth()) deactivate();
}

void Bullet::draw()
{
	resetPosition().move(xPos, yPos, 0);
}

void Bullet::tick(uint32_t e)
{
	elapsed = float(e) / 1000.0f;
}

void Bullet::collision(Tactile* t, uint8_t)
{
	if(hidden) return;
	if((t->isOfType<Ship>() && dir > 0.0f) || (t->isOfType<Enemy>() && dir < 0.0f)) return;
	dying = true;
}

void Bullet::activate()
{
	hidden = false;
	xPos = spawner->getX();
	yPos = spawner->getY() + dir/2.0f * (spawner->getCollH()+collHeight);
}

void Bullet::deactivate()
{
	dying = false;
	hidden = true;
	xPos = -1000;
	yPos = -1000;
}

bool Bullet::active() const
{
	return !hidden;
}