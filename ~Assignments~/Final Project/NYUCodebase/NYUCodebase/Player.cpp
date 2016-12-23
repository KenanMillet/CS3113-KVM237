#include "Player.h"
#include "Entities.h"
#include "Texture.h"
#include <cmath>
#include <algorithm>
#include "logger.h"
#include "Entities.h"

Player::Player(const char* texture, const char* bulletTexture, SDL_Scancode u, SDL_Scancode d, SDL_Scancode l, SDL_Scancode r, SDL_Scancode f)
	:	TactileEntity::Model(texture, getSpriteSheet("sheet.png", "sheet.xml"), 0.3f),
		EventDependent({SDL_KEYDOWN, SDL_KEYUP}),
		bullet(new Bullet(this, 1.0f, bulletTexture)), u(u), d(d), l(l), r(r), f(f)
{
	lives += 3;
	if(numInstances++ == 0)
	{
		fireSound = Mix_LoadWAV("PlayerFireSound.wav");
		damageSound = Mix_LoadWAV("PlayerDamageSound.wav");
		explosionSound = Mix_LoadWAV("PlayerExplosionSound.wav");
	}
}

Player::~Player()
{
	if(--numInstances <= 0)
	{
		numInstances = 0;
		Mix_FreeChunk(fireSound);
		Mix_FreeChunk(damageSound);
		Mix_FreeChunk(explosionSound);
	}
}

Player& Player::operator=(const Player& o)
{
	TactileEntity::operator=(o);
	EventDependent::operator=(o);
	accelx = o.accelx;
	accely = o.accely;
	velx = o.velx;
	vely = o.vely;
	lives = o.lives;
	u = o.u;
	d = o.d;
	l = o.l;
	r = o.r;
	f = o.f;
	elapsed = 0;
	return *this;
}

void Player::eventFilter(SDL_Event event)
{
	SDL_Scancode scancode = event.key.keysym.scancode;
	Uint32 type = event.type;
	if(scancode == u)
	{
		if(type == SDL_KEYDOWN) accely = 4.0f;
		if(type == SDL_KEYUP) accely = 0.0f;
	}
	if(scancode == d)
	{
		if(type == SDL_KEYDOWN) accely = -4.0f;
		if(type == SDL_KEYUP) accely = 0.0f;
	}
	if(scancode == l)
	{
		if(type == SDL_KEYDOWN) accelx = -4.0f;
		if(type == SDL_KEYUP) accelx = 0.0f;
	}
	if(scancode == r)
	{
		if(type == SDL_KEYDOWN) accelx = 4.0f;
		if(type == SDL_KEYUP) accelx = 0.0f;
	}
	if(scancode == f)
	{
		if(type == SDL_KEYDOWN && ready()) fire();
	}
}

void Player::setup()
{
	if(lives < 1)
	{
		suicide();
		return;
	}
	xPos += velx * elapsed;
	yPos += vely * elapsed;
	velx += accelx * elapsed;
	vely += accely * elapsed;

	if(outOfBoundsWest())
	{
		xPos = level()->wBound();
		velx = ((velx < 0) ? 0 : velx);
	}
	if(outOfBoundsEast())
	{
		xPos = level()->eBound();
		velx = ((velx > 0) ? 0 : velx);
	}
	if(outOfBoundsSouth() && vely < 0)
	{
		yPos = level()->sBound();
		vely = ((vely < 0) ? 0 : vely);
	}
	if(outOfBoundsNorth() && vely > 0)
	{
		yPos = level()->nBound();
		vely = ((vely > 0) ? 0 : vely);
	}
}

void Player::draw()
{
	resetPosition().move(xPos, yPos, 0);
}

void Player::tick(uint32_t e)
{
	elapsed = float(e) / 1000.0f;
	if(iTime > 0.0f) iTime = std::max(iTime - elapsed, 0.0f);
}

void Player::touch(Tactile* t, Vector)
{
	if(iTime > 0.0f) return;
	if((t->isOfType<Bullet>() && dynamic_cast<Bullet*>(t)->dir < 0) || t->isOfType<Enemy>())
	{
		iTime = 3.0f;
		--lives;
		Mix_PlayChannel(-1, ((lives > 0) ? damageSound : explosionSound), 0);
	}
}

void Player::fire()
{
	if(lives < 1) return;
	bullet->setLevel(level());
	bullet->activate();
	Mix_PlayChannel(-1, fireSound, 0);
}

bool Player::ready()
{
	return (!bullet->active());
}

uint8_t Player::lives = 0;
size_t Player::numInstances = 0;
Mix_Chunk* Player::fireSound = nullptr;
Mix_Chunk* Player::damageSound = nullptr;
Mix_Chunk* Player::explosionSound = nullptr;