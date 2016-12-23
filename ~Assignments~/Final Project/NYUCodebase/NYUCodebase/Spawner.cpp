#include "Spawner.h"
#include "Entity.h"

Spawner::Spawner(const Vector& location)
	: location(location)
{
}

Spawner::~Spawner()
{
	for(Entity* e : entities)
	{
		e->spawner = nullptr;
		delete e;
	}
	for(Entity* e : corpses)
	{
		e->spawner = nullptr;
		delete e;
	}
}

size_t Spawner::numSpawn() const
{
	return entities.size();
}

void Spawner::setupEntity(Entity* entity, const Vector& position, const Vector& rotation, const Vector& scale)
{
	//TODO: Make this work with vectors... This x/y/zPos stuff is super outdated
	auto res = entities.insert(entity);
	(*res.first)->xPos = position.x;
	(*res.first)->yPos = position.y;
	(*res.first)->zPos = position.z;
	entity->spawner = this;
}