#include "Particle.h"
#include "Renderer.h"

Particle::Particle(const Vector& position, const Vector& velocity, const Vector& gravity, float lifespan)
	: position(position), velocity(velocity), gravity(gravity), lifespan(lifespan), age(0.0f)
{
	defaultRender->remove(this);
}

void Particle::draw()
{
}

void Particle::tick(uint32_t elapsed)
{
	age += float(elapsed) / 1000.0f;
	position += velocity * elapsed;
	velocity += gravity;
}

bool Particle::isAlive() const
{
	return age < lifespan;
}

void Particle::revive()
{
	age = 0.0f;
}

void Particle::revive(float lifespan)
{
	revive(position, velocity, gravity, lifespan);
}

void Particle::revive(const Vector& velocity, float lifespan)
{
	revive(position, velocity, gravity, lifespan);
}

void Particle::revive(const Vector& position, const Vector& velocity, float lifespan)
{
	revive(position, velocity, gravity, lifespan);
}

void Particle::revive(const Vector& position, const Vector& velocity, const Vector& gravity, float lifespan)
{
	this->position = position;
	this->velocity = velocity;
	this->gravity = gravity;
	this->lifespan = lifespan;
	revive();
}
