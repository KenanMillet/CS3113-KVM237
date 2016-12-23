#include "TactileEntity.h"

bool TactileEntity::outOfBoundsNorth()
{
	return (level()->nBound() < yPos + collHeight / 2.0f);
}

bool TactileEntity::outOfBoundsEast()
{
	return (level()->eBound() < xPos + collWidth / 2.0f);
}

bool TactileEntity::outOfBoundsSouth()
{
	return (level()->sBound() > yPos - collHeight / 2.0f);
}

bool TactileEntity::outOfBoundsWest()
{
	return (level()->wBound() > xPos - collWidth / 2.0f);
}