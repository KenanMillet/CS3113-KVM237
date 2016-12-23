#pragma once
#include "Entity.h"

class Particle : public Entity
{
public:
	Particle(const Vector&, const Vector&, const Vector&, float);

	virtual void draw();
	virtual void tick(uint32_t);
	bool isAlive() const;
	void revive();
	void revive(float);
	void revive(const Vector&, float);
	void revive(const Vector&, const Vector&, float);
	void revive(const Vector&, const Vector&, const Vector&, float);
protected:
	Vector position;
	Vector gravity;
	Vector velocity;

	float lifespan;
	float age;
};