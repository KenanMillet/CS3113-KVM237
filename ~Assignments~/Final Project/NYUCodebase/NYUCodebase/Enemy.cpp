#include "Enemy.h"
#include "Texture.h"
#include "Entities.h"
#include "MainGame.h"

Enemy::Enemy()
	:	TactileEntity::Model("enemyGreen1.png", getSpriteSheet("sheet.png", "sheet.xml"), 0.3f),
		elapsed(0.0f), lastFire(0.0f), destroyed(false), bullet(new Bullet(this, -1.0f, "laserGreen07.png"))
{
	if(numInstances++ == 0)
	{
		fireSound = Mix_LoadWAV("EnemyFireSound.wav");
		explosionSound = Mix_LoadWAV("EnemyExplosionSound.wav");
	}
}

Enemy::~Enemy()
{
	if(--numInstances <= 0)
	{
		numInstances = 0;
		Mix_FreeChunk(fireSound);
		Mix_FreeChunk(explosionSound);
	}
}

Enemy& Enemy::operator=(const Enemy& o)
{
	TactileEntity::operator=(o);
	elapsed = 0;
	lastFire = 0;
	destroyed = o.destroyed;
	return *this;
}

void Enemy::setup()
{
	if(destroyed)
	{
		suicide();
		return;
	}
	yPos -= spd * elapsed;
	if(!outOfBoundsNorth() && ready()) fire();
}

void Enemy::draw()
{
	resetPosition().move(xPos, yPos, 0);
}

void Enemy::tick(uint32_t e)
{
	elapsed = float(e) / 1000.0f;
	lastFire += elapsed;
}

void Enemy::touch(Tactile* t, Vector)
{
	if((t->isOfType<Bullet>() && dynamic_cast<Bullet*>(t)->dir > 0) || t->isOfType<Player>())
	{
		Mix_PlayChannel(-1, explosionSound, 0);
		destroyed = true;
		MainGame::score++;
	}
}

void Enemy::fire()
{
	Mix_PlayChannel(-1, fireSound, 0);
	bullet->setLevel(level());
	bullet->activate();
	lastFire = 0.0f;
}

bool Enemy::ready()
{
	return (!bullet->active() && ((spd * spd * lastFire * 0.2f) > distribution(generator)));
}

float Enemy::spd = 0.5f;
std::default_random_engine Enemy::generator;
std::uniform_real_distribution<float> Enemy::distribution(0.0f, 99.99f);
size_t Enemy::numInstances = 0;
Mix_Chunk* Enemy::fireSound = nullptr;
Mix_Chunk* Enemy::explosionSound = nullptr;