#pragma once
#include "TactileEntity.h"

class Bullet : public TactileEntity
{
public:
	Bullet(TactileEntity*, float, const char*);

	virtual void setup();
	virtual void draw();

	virtual void tick(uint32_t);

	virtual void touch(Tactile*, Vector);

	void activate();
	void deactivate();
	bool active() const;

	const float dir;

	using Entity::setLevel;
	using Entity::suicide;

private:
	bool hidden;
	bool dying;

	TactileEntity* spawner;

	float spd;
	float elapsed;
};