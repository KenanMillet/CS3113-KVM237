#include "Tactile.h"
#include "CollisionHandler.h"
#include <limits>

using namespace std;

Tactile::Tactile(float collWidth, float collHeight, float collDepth, bool posLock, CollisionHandler* handler)
	: thehandler(handler), collWidth(collWidth), collHeight(collHeight), collDepth(collDepth), posLock(posLock)
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

bool Tactile::immobile() const
{
	return posLock;
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

void Tactile::onCollision(Tactile* t, Vector v)
{
	resolveCollision(t, v);
}

bool Tactile::resolveCollision(Tactile* t, Vector v)
{
	if(immobile()) return true;
	if(!t->immobile()) v *= 0.5f;
	xPos += v.x;
	yPos += v.y;
	zPos += v.z;

	return false;
}

void Tactile::touch(Tactile*, Vector)
{
}

float Tactile::moveX()
{
	xPos += dispX;
	return dispX;
}

float Tactile::moveY()
{
	yPos += dispY;
	return dispY;
}

float Tactile::moveZ()
{
	zPos += dispZ;
	return dispZ;
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