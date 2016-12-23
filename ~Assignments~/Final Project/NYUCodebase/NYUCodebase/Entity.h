#pragma once

#include "Model.h"
#include "Tickable.h"
#include "Spawner.h"
#include "Level.h"

class Entity : virtual public Model, virtual public Tickable
{
	friend Level;
	friend Spawner;
public:
	Entity();
	virtual ~Entity();

	virtual void Tick(uint32_t);
protected:
	void suicide();
	void separate();
	const Level* level() const;
	void setLevel(const Level*);
	
private:
	Spawner* spawner;
	Level* _level;
};