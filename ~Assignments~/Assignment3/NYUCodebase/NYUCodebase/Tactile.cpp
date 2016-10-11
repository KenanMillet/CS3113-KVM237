#include "Tactile.h"
#include "CollisionHandler.h"

Tactile::Tactile(float collWidth, float collHeight, float collDepth, CollisionHandler* handler)
	: thehandler(handler), collWidth(collWidth), collHeight(collHeight), collDepth(collDepth)
{
	thehandler->add(this);
}

Tactile::Tactile(const Tactile& original)
	: thehandler(original.thehandler), collWidth(original.collWidth), collHeight(original.collHeight), collDepth(original.collDepth)
{
	thehandler->add(this);
}

Tactile::Tactile(Tactile&& temp)
	: thehandler(temp.thehandler), collWidth(temp.collWidth), collHeight(temp.collHeight), collDepth(temp.collDepth)
{
	thehandler->add(this);
}

Tactile::~Tactile()
{
	thehandler->remove(this);
}

Tactile & Tactile::operator=(const Tactile& original)
{
	if(&original != this)
	{
		if(thehandler != original.thehandler)
		{
			thehandler->remove(this);
			thehandler = original.thehandler;
			thehandler->add(this);
		}
	}
	return *this;
}

Tactile & Tactile::operator=(Tactile&& temp)
{
	if(&temp != this)
	{
		if(thehandler != temp.thehandler)
		{
			thehandler->remove(this);
			thehandler = temp.thehandler;
			thehandler->add(this);
		}
	}
	return *this;
}

Tactile& Tactile::noCollisionWith(Tactile* t)
{
	thehandler->addException(this, t);
	return *this;
}

float Tactile::getCollW()
{
	return collWidth;
}

float Tactile::getCollH()
{
	return collHeight;
}

float Tactile::getCollD()
{
	return collDepth;
}

CollisionHandler* Tactile::defaultCollisionHandler= &::handleCollisions;