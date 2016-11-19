#pragma once

#include "Model.h"
#include "Tickable.h"
#include "Level.h"

class Entity : virtual public Model, virtual public Tickable
{
	friend void Level::setupEntity(Entity*, float, float, float);
public:
	Entity();
	virtual ~Entity() = default;

	virtual void Tick(uint32_t);
protected:
	const Level* level;
};