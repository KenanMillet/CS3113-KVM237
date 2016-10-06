#pragma once

#include "Model.h"
#include "Tickable.h"

class Entity : virtual public Model, virtual public Tickable
{
public:
	Entity();
	virtual ~Entity() = default;

	virtual void Tick(uint32_t);
};