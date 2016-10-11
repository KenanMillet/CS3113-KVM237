#pragma once
#include "TactileEntity.h"
#include <random>

class Bullet;

class Enemy : public TactileEntity
{
	friend Bullet;
public:
	Enemy();

	virtual void setup();
	virtual void draw();
	virtual void clean();

	virtual void tick(uint32_t);

	virtual void collision(Tactile*, uint8_t);
private:
	void fire();
	bool ready();

	float elapsed, lastFire;
	bool destroyed;

	Bullet* bullet;

	static float spd, dir, ydisp;
	static bool forward, ydispCalc;
	static std::default_random_engine generator;
	static std::uniform_real_distribution<float> distribution;
};