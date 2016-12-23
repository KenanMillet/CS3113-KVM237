#pragma once
#include "TactileEntity.h"
#include <SDL_mixer.h>
#include <random>

class MainGame;
class Bullet;

class Enemy : public TactileEntity
{
	friend Bullet;
	friend MainGame;
public:
	Enemy();
	~Enemy();

	Enemy& operator=(const Enemy&);

	virtual void setup();
	virtual void draw();

	virtual void tick(uint32_t);

	virtual void touch(Tactile*, Vector);

	static float spd;
private:
	void fire();
	bool ready();

	float elapsed, lastFire;
	bool destroyed;

	Bullet* bullet;

	static Mix_Chunk* fireSound;
	static Mix_Chunk* explosionSound;
	static size_t numInstances;

	static std::default_random_engine generator;
	static std::uniform_real_distribution<float> distribution;
};