#pragma once
#include "Tactile.h"
#include "Entity.h"

class TactileEntity : virtual public Entity, virtual public Tactile
{
public:
	virtual ~TactileEntity() = default;

	virtual void collisionX(Tactile*, uint8_t);
	virtual void collisionY(Tactile*, uint8_t);
	virtual void collisionZ(Tactile*, uint8_t);
protected:
	bool outOfBoundsNorth();
	bool outOfBoundsEast();
	bool outOfBoundsSouth();
	bool outOfBoundsWest();
};