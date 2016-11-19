#include "TactileEntity.h"

void TactileEntity::collisionX(Tactile* t, uint8_t s)
{
	Tactile::collisionX(t, s);
}

void TactileEntity::collisionY(Tactile* t, uint8_t s)
{
	Tactile::collisionY(t, s);
}

void TactileEntity::collisionZ(Tactile* t, uint8_t s)
{
	Tactile::collisionZ(t, s);
}

bool TactileEntity::outOfBoundsNorth()
{
	return (level->nBound() < yPos + collHeight / 2.0f);
}

bool TactileEntity::outOfBoundsEast()
{
	return (level->eBound() < xPos + collWidth / 2.0f);
}

bool TactileEntity::outOfBoundsSouth()
{
	return (level->sBound() > yPos - collHeight / 2.0f);
}

bool TactileEntity::outOfBoundsWest()
{
	return (level->wBound() > xPos - collWidth / 2.0f);
}