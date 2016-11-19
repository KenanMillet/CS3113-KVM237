#pragma once
#include "Model.h"
#include <cstdint>
#include <set>
#include <typeinfo>

#define INFINITESIMAL 0.00006103515625f

class CollisionHandler;

class Tactile : virtual public Model
{
public:
	Tactile(float = 0, float = 0, float = 0, CollisionHandler* = defaultCollisionHandler);
	Tactile(const Tactile&);
	Tactile(Tactile&&);
	virtual ~Tactile();

	Tactile& operator=(const Tactile&);
	Tactile& operator=(Tactile&&);

	virtual void collision(Tactile*, uint8_t);
	virtual void collisionX(Tactile*, uint8_t);
	virtual void collisionY(Tactile*, uint8_t);
	virtual void collisionZ(Tactile*, uint8_t);

	virtual void touch(Tactile*, uint8_t);

	float moveX();
	float moveY();
	float moveZ();

	float getCollW();
	float getCollH();
	float getCollD();

	template<class T> bool isOfType() const;

	static CollisionHandler* defaultCollisionHandler;
protected:
	Tactile& noCollisionWith(Tactile*);

	float collWidth, collHeight, collDepth;
	float dispX, dispY, dispZ;
private:
	CollisionHandler* thehandler;
};

template<class T>
bool Tactile::isOfType() const
{
	return typeid(T) == typeid(*this);
}