#pragma once
#include "Model.h"
#include <cstdint>

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

	virtual void collision(Tactile*, uint8_t) = 0;

	float getCollW();
	float getCollH();
	float getCollD();

	static CollisionHandler* defaultCollisionHandler;
protected:
	Tactile& noCollisionWith(Tactile*);

	float collWidth, collHeight, collDepth;
private:
	CollisionHandler* thehandler;
};