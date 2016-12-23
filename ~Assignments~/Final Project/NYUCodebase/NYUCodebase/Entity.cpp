#include "Entity.h"

Entity::Entity()
	: spawner(nullptr)
{
}

Entity::~Entity()
{
	if(spawner) spawner->disown(this);
}

void Entity::Tick(uint32_t)
{
}

void Entity::suicide()
{
	if(spawner) spawner->despawn(this);
}

void Entity::separate()
{
	if(spawner) spawner->disown(this);
}

const Level* Entity::level() const
{
	return _level;
}

void Entity::setLevel(const Level* l)
{
	_level = const_cast<Level*>(l);
}
