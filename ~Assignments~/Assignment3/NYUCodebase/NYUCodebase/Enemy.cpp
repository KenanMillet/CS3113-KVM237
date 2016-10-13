#include "Enemy.h"
#include "Texture.h"
#include "Bullet.h"

Enemy::Enemy()
	:	TactileEntity::Model("enemyBlue1.png", getSpriteSheet("sheet.png", "sheet.xml"), 0.3f),
		TactileEntity::Tactile(width(), height()),
		elapsed(0.0f), lastFire(0.0f), destroyed(false), bullet(new Bullet(this, -1.0f))
{
}

void Enemy::setup()
{
	if(destroyed)
	{
		xPos = -1000.0f;
		yPos = -1000.0f;
		return;
	}
	if(ydisp >= collHeight) forward = false;
	if(!forward) xPos += spd * elapsed * dir;
	if(forward)
	{
		if(ydispCalc) ydisp += spd * elapsed;
		yPos -= spd * elapsed;
	}
	if(ready()) fire();
	ydispCalc = false;
}

void Enemy::draw()
{
	resetPosition().move(xPos, yPos, 0);
}

void Enemy::clean()
{
	if(destroyed) return;
	if(outOfBoundsEast() && !forward)
	{
		xPos = level->eBound() - collWidth / 2.0f;
		dir *= -1.0f;
		forward = true;
		ydisp = 0.0f;
	}
	if(outOfBoundsWest() && !forward)
	{
		xPos = level->wBound() + collWidth / 2.0f;
		dir *= -1.0f;
		forward = true;
		ydisp = 0.0f;
	}
	ydispCalc = true;
}

void Enemy::tick(uint32_t e)
{
	elapsed = float(e) / 1000.0f;
	lastFire += elapsed;
}

void Enemy::collision(Tactile* t, uint8_t)
{
	if(t->isOfType<Bullet>())
	{
		if(dynamic_cast<Bullet*>(t)->dir > 0) destroyed = true;
	}
}

void Enemy::fire()
{
	bullet->level = level;
	bullet->activate();
	lastFire = 0.0f;
}

bool Enemy::ready()
{
	if(destroyed) return false;
	return (!bullet->active() && ((spd * spd * lastFire * 0.01f) > distribution(generator)));
}

float Enemy::spd = 0.5f;
float Enemy::dir = 1.0f;
float Enemy::ydisp = 0.0f;
bool Enemy::forward = false;
bool Enemy::ydispCalc = true;
std::default_random_engine Enemy::generator;
std::uniform_real_distribution<float> Enemy::distribution(0.0f, 99.99f);