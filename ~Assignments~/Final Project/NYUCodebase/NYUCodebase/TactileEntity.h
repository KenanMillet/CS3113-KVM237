#pragma once
#include "Tactile.h"
#include "Entity.h"

class TactileEntity : virtual public Entity, virtual public Tactile
{
public:
	virtual ~TactileEntity() = default;
protected:
	bool outOfBoundsNorth();
	bool outOfBoundsEast();
	bool outOfBoundsSouth();
	bool outOfBoundsWest();
};