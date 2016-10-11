#pragma once
#include "TactileEntity.h"

class Bullet : public TactileEntity
{
public:
	Bullet(TactileEntity*, float);

	virtual void setup();
	virtual void draw();

	virtual void tick(uint32_t);

	virtual void collision(Tactile*, uint8_t);

	void activate();
	void deactivate();
	bool active() const;

	using Entity::level;

	const float dir;

private:
	bool hidden;
	bool dying;

	TactileEntity* spawner;

	float spd;
	float elapsed;
};